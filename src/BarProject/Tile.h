//
// Created by Alvarado, Alejandro on 4/15/17.
//

#ifndef TEST_CLIENT_TILE_H
#define TEST_CLIENT_TILE_H


#include "Queue.h"

class Tile {
public:
    bool hasWallAt[4] = {false, false, false, false};
    Tile* successors[4] = {nullptr, nullptr, nullptr, nullptr};
    int row = 0;
    int col = 0;
    Queue<int> *route;
    Tile(int row, int col);

    String key;
    virtual ~Tile();
};


#endif //TEST_CLIENT_TILE_H
