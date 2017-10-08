//
// Created by Alvarado, Alejandro on 4/15/17.
//

#ifndef TEST_CLIENT_TILE_H
#define TEST_CLIENT_TILE_H


#include "Queue.h"

class Tile {
public:
    bool hasWallAt[4] = {false, false, false, false};
    int row;
    int col;
    bool visited = false;
    Queue<int> *route;
    Tile();

    virtual ~Tile();
};


#endif //TEST_CLIENT_TILE_H
