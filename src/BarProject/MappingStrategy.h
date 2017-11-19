#ifndef MAZENAV_MAPPING_H
#define MAZENAV_MAPPING_H

#include "WallDetector.h"
#include "HashMap.h"
#include "Tile.h"
#include "PriorityQueue.h"
#include "Navigator.h"

#define DIRECTION_W 0
#define DIRECTION_N 1
#define DIRECTION_E 2
#define DIRECTION_S 3

class MappingStrategy {
public:
    MappingStrategy(WallDetector* frontDetector, WallDetector* leftDetector, WallDetector* rightDetector, Navigator* navigator);
    void init();
private:
    //Tiles we know are reachable
    HashMap<Tile*> *maze;

    //Only the keys matter, if a key exists here, we've visited that tile before (and discovered its succesors)
    HashMap<int*> *visited;

    //The keys to pending tiles
    PriorityQueue<String*> *pending;
    
    int facing = DIRECTION_N;

    Navigator* navigator;

    WallDetector* front;
    WallDetector* left;
    WallDetector* right;




    void face(int newDirection);
    void afterDetectingWalls(Tile* tile, bool ignoreRear);
    Tile* findTile(int row, int col);    


    int displacement[4][2] = {   {-1, 0}, //W
                                {0, 1},  //N
                                {1, 0},  //E
                                {0, -1}  //S
                            };
                            
                            //W N E S
    int invertDirection[4] = {DIRECTION_E, DIRECTION_S, DIRECTION_W, DIRECTION_N};

    const char* directionName[4] = {"W", "N", "E", "S"};
};



#endif