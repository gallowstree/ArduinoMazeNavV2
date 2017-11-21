//
// Created by Alvarado, Alejandro on 5/27/17.
//

#ifndef TEST_CLIENT_SEARCH_H
#define TEST_CLIENT_SEARCH_H

#include "Queue.h"
#include "Tile.h"

class Search {
    public:
    static void dfs(Tile* startTile, Tile* goalTile, Queue<int> * route);
    static void bfs(Tile* startTile, Tile* goalTile, Queue<int> * route);
    static void astar(Tile* startTile, Tile* goalTile, Queue<int> * route);
    private:
    static int euclidean_distance(Tile * a, Tile * b);
    static char * visitedValue = "v";
};


#endif //TEST_CLIENT_SEARCH_H
