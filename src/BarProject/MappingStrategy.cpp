#include "MappingStrategy.h"
#include "Arduino.h"
#include "Search.h"

MappingStrategy::MappingStrategy(WallDetector* frontDetector, WallDetector* leftDetector, WallDetector* rightDetector, Navigator* navigator)
: front(frontDetector),right(rightDetector),left(leftDetector), navigator(navigator) {
    maze = new HashMap<Tile*>();
    visited = new HashMap<char*>();
    pending = new PriorityQueue<String*>();     
}

Tile* MappingStrategy::init(int direction) {
    Tile* startTile = new Tile(0,0);
    maze->put(startTile->key.c_str(), startTile);
    navigator->facing = direction;
    detectWallsAt(startTile, false);
    afterDetectingWalls(startTile, false);
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
    navigator->executeRoute(&route);

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
}

void MappingStrategy::afterDetectingWalls(Tile* tile, bool ignoreRear) {
    //Mark the tile as visited
    Serial.print("marking as visited "); Serial.println(tile->key.c_str());

    visited->put(tile->key.c_str(), visitedValue);

    for (int d = DIRECTION_W; d <= DIRECTION_S; d++) {
        if (d == invertDirection[navigator->facing] && ignoreRear)
            continue;

        if (!tile->hasWallAt[d]) {
            
            int successorRow = tile->row + displacement[d][0];
            int successorCol = tile->col + displacement[d][1];
            Serial.print("can move to "); Serial.println(directionName[d]);
            Serial.print("coords: "); Serial.print(successorRow); Serial.print(" "); Serial.println(successorCol);
            
            Tile* successor = findTile(successorRow, successorCol);
            if (successor == nullptr) {
                Serial.println("Successor was not found... it will be created");
                successor = new Tile(successorRow, successorCol);

                maze->put(successor->key.c_str(), successor);
            }
        
            tile->successors[d] = successor;
            Serial.print("Col Suc:");
            Serial.print(tile->successors[d]->col);
            Serial.print("Row Suc:");
            Serial.println(tile->successors[d]->row);
            successor->successors[invertDirection[d]] = tile;
            successor->hasWallAt[invertDirection[d]] = false;
            
            if (visited->get(successor->key.c_str()) == nullptr) {
                int priority = d == navigator->facing ? 0 : 1;
                Serial.print("Successor has not been visited, will enqueue it with priority "); Serial.println(priority);
                pending->enqueue(&successor->key, priority);
            }            
        }
    }
}

Tile* MappingStrategy::findTile(int row, int col) {
    String key = String(row);
    key.concat(",");
    key.concat(col);  

    return maze->get(key.c_str());
}