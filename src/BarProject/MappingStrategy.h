#ifndef MAZENAV_MAPPING_H
#define MAZENAV_MAPPING_H

#include "WallDetector.h"
#include "HashMap.h"
#include "Tile.h"
#include "PriorityQueue.h"
#include "Navigator.h"

class MappingStrategy {
public:
    MappingStrategy(HashMap<Tile*>* maze, WallDetector* frontDetector, WallDetector* leftDetector, WallDetector* rightDetector, Navigator* navigator);
    Tile* init(int direction);
    Tile* step(Tile* current);
private:
    //Tiles we know are reachable
    HashMap<Tile*> *maze;

    //Only the keys matter, if a key exists here, we've visited that tile before (and discovered its succesors)
    HashMap<char*> *visited;
    //The keys to pending tiles
    PriorityQueue<String*> *pending;  

    Navigator* navigator;

    WallDetector* front;
    WallDetector* left;
    WallDetector* right;

    int currPriority = 1000;

    WallDetector* wallDetectorForDirection[4][4] = {{front, right, nullptr, left},  
                                                    {left, front, right, nullptr}, 
                                                    {nullptr, left, front, right}, 
                                                    {right, nullptr, left, front}}; 
    

    void detectWallsAt(Tile* tile, bool ignoreRear);
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
    char* visitedValue = "v";

    
};



#endif