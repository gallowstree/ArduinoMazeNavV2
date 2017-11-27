#include "MappingStrategy.h"
#include "Arduino.h"
#include "Search.h"
#include "EventLogger.h"

int MappingStrategy::displacement[4][2] ;

MappingStrategy::MappingStrategy(HashMap<Tile*> * maze, WallDetector* frontDetector, WallDetector* leftDetector, WallDetector* rightDetector, Navigator* navigator)
: maze(maze),front(frontDetector),right(rightDetector),left(leftDetector), navigator(navigator) {
    visited = new HashMap<char*>();
    pending = new PriorityQueue<String*>();     
}

Tile* MappingStrategy::init(int direction) {
    Tile* startTile = new Tile(0,0);
    maze->put(startTile->key.c_str(), startTile);
    navigator->facing = direction;
    EventLogger::updateLocation(direction, 0, 0);
    detectWallsAt(startTile, false);
    afterDetectingWalls(startTile, false);
    return startTile;
}

Tile* MappingStrategy::step(Tile* current) {
    if (pending->isEmpty()) 
        return nullptr;
    
    int ignored = 0;
    String* key = pending->dequeue(&ignored);
    Serial.print("Next node to visit is: "); Serial.println(*key);
    Tile* goal = maze->get(key->c_str());

    Queue<int> route;
    Search::astar(current, goal, &route);
    Serial.print("Route: ");
    route.print();
    navigator->executeRoute(&route, current->row, current->col);

    current = goal;
    detectWallsAt(current, true);
    afterDetectingWalls(current, true);
    return current;
}

void MappingStrategy::detectWallsAt(Tile* tile, bool ignoreRear) {
    Serial.println(String("Detecting walls for tile") + tile->key);
    for (int d = DIRECTION_W; d <= DIRECTION_S; d++) 
    { 
        if (d == invertDirection[navigator->facing]) {
            if (ignoreRear)
                continue;
            else
                navigator->faceDirection(d);
        }

        WallDetector* detector = wallDetectorForDirection[navigator->facing][d];  
        if (detector != nullptr)
            tile->hasWallAt[d] = detector->isFacingWall();
        Serial.print("     has wall at "); Serial.print(directionName[d]); Serial.print(" "); Serial.println(tile->hasWallAt[d]);
    }
    EventLogger::discoveredTile(tile);
}

void MappingStrategy::afterDetectingWalls(Tile* tile, bool ignoreRear) {
    //Mark the tile as visited
    Serial.print("marking as visited "); Serial.println(tile->key.c_str());

    visited->put(tile->key.c_str(), visitedValue);

    for (int d = DIRECTION_W; d <= DIRECTION_S; d++) {
        if (d == invertDirection[navigator->facing] && ignoreRear)
            continue;

        if (!tile->hasWallAt[d]) {
            
            int successorRow = tile->row + MappingStrategy::displacement[d][0];
            int successorCol = tile->col + MappingStrategy::displacement[d][1];
            Serial.print("can move to "); Serial.println(directionName[d]);
            Serial.print("coords: "); Serial.print(successorRow); Serial.print(" "); Serial.println(successorCol);
            
            Tile* successor = findTile(successorRow, successorCol);
            if (successor == nullptr) {
                Serial.println("Successor was not found... it will be created");
                successor = new Tile(successorRow, successorCol);

                maze->put(successor->key.c_str(), successor);
            }
        
            tile->successors[d] = successor;
            successor->successors[invertDirection[d]] = tile;
            successor->hasWallAt[invertDirection[d]] = false;
            
            if (visited->get(successor->key.c_str()) == nullptr) {
                int priority = d == navigator->facing ? currPriority - 1 : currPriority;
                Serial.print("Successor has not been visited, will enqueue it with priority "); Serial.println(priority);
                pending->enqueue(&successor->key, priority);
            }            
        }
    }

    currPriority--;
}

Tile* MappingStrategy::findTile(int row, int col) {
    String key = String(row);
    key.concat(",");
    key.concat(col);  

    return maze->get(key.c_str());
}