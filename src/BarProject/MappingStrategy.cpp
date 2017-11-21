#include "MappingStrategy.h"
#include "Arduino.h"
#include "Search.h"

MappingStrategy::MappingStrategy(WallDetector* frontDetector, WallDetector* leftDetector, WallDetector* rightDetector, Navigator* navigator)
: front(frontDetector),right(rightDetector),left(leftDetector), navigator(navigator) {
    maze = new HashMap<Tile*>();
    visited = new HashMap<char*>();
    pending = new PriorityQueue<String*>();     
}

void MappingStrategy::init() {
    Tile* startTile = new Tile(0,0);
    maze->put(startTile->key.c_str(), startTile);
    current = startTile;

    startTile->hasWallAt[DIRECTION_N] = false;//front->isFacingWall();
    startTile->hasWallAt[DIRECTION_W] = false;//left->isFacingWall();
    startTile->hasWallAt[DIRECTION_E] = false;//right->isFacingWall();
        
    navigator->faceDirection(DIRECTION_W);        
    startTile->hasWallAt[DIRECTION_S] = true;//left->isFacingWall();
    
    afterDetectingWalls(startTile, false);
}



bool MappingStrategy::step() {
    if (pending->isEmpty()) 
        return true;
    
    int ignored = 0;
    String key = pending->dequeue(&ignored);
    Serial.print("Next node to visit is: "); Serial.println(key);
    Tile* goal = maze->get(key.c_str());

    Queue<int> route;
    Search::astar(current, goal, &route);
    navigator->executeRote(&route);

    current = goal;
}

void MappingStrategy::afterDetectingWalls(Tile* tile, bool ignoreRear) {
    //Mark the tile as visited
    Serial.print("marking as visited "); Serial.println(tile->key.c_str());
    char * value; *value = 'v';
    visited->put(tile->key.c_str(), value);

    for (int d = DIRECTION_W; d <= DIRECTION_S; d++) {
        if (d == invertDirection[navigator->facing] && ignoreRear)
            continue;

        if (!tile->hasWallAt[d]) {
            
            int successorRow = tile->row + displacement[d][1];
            int successorCol = tile->col + displacement[d][0];
            Serial.print("can move to "); Serial.println(directionName[d]);
            Serial.print("coords: "); Serial.print(successorRow); Serial.print(" "); Serial.println(successorCol);
            
            Tile* successor = findTile(successorRow, successorCol);
            if (successor == nullptr) {
                Serial.println("Successor was not found... it will be created");
                successor = new Tile(successorRow, successorCol);
                maze->put(successor->key.c_str(), successor);
            }

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