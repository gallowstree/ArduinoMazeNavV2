//
// Created by Alvarado, Alejandro on 5/27/17.
//

#ifndef TEST_CLIENT_SEARCH_H
#define TEST_CLIENT_SEARCH_H


#include "Maze.h"
#include "Queue.h"

class Search {
    public:
    static void dfs(Maze * maze, Queue<int> * route);
    static void bfs(Maze * maze, Queue<int> * route);
    static void astar(Maze * maze, Queue<int> * route);
    private:
    static int euclidean_distance(Tile * a, Tile * b);
};


#endif //TEST_CLIENT_SEARCH_H
