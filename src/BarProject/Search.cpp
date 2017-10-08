//
// Created by Alvarado, Alejandro on 5/27/17.
//
#include <math.h>
#include "Search.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

void Search::dfs(Maze * maze, Queue<int> * route)
{
    Stack <Tile *> tiles;
    tiles.push(maze->startTile);
    while(!tiles.isEmpty())
    {
        Tile * currentTile = tiles.pop();
        if(!currentTile->visited) {
            currentTile->visited = true;
            if (currentTile == maze->goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            auto successors = new Tile *[4]();
            maze->getSuccessors(currentTile->row, currentTile->col, successors);

            for (int i = 0; i < 4; i++) {
                if (successors[i] != nullptr && !successors[i]->visited) {
                    delete successors[i]->route;
                    successors[i]->route = new Queue<int>;
                    if (!currentTile->route->isEmpty()) {
                        currentTile->route->copyQueue(successors[i]->route);
                    }

                    successors[i]->route->enqueue(i);
                    tiles.push(successors[i]);
                }
            }
            delete[] successors;
        }
    }
    maze->resetVisitedTiles();
}

void Search::bfs(Maze * maze, Queue<int> * route)
{
    Queue <Tile *> tiles;
    tiles.enqueue(maze->startTile);
    while(!tiles.isEmpty())
    {
        Tile * currentTile = tiles.dequeue();
        if(!currentTile->visited)
        {
            currentTile->visited = true;
            if (currentTile == maze->goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            auto successors = new Tile *[4]();
            maze->getSuccessors(currentTile->row, currentTile->col, successors);

            for (int i = 0; i < 4; i++) {
                if (successors[i] != nullptr && !successors[i]->visited) {
                    delete successors[i]->route;
                    successors[i]->route = new Queue<int>;
                    if (!currentTile->route->isEmpty()) {
                        currentTile->route->copyQueue(successors[i]->route);
                    }

                    successors[i]->route->enqueue(i);
                    tiles.enqueue(successors[i]);
                }
            }
            delete[] successors;
        }
    }
    maze->resetVisitedTiles();
}

void Search::astar(Maze *maze, Queue<int> *route) {
    PriorityQueue<Tile *> tiles;
    tiles.enqueue(maze->startTile,euclidean_distance(maze->startTile,maze->goalTile));
    while(!tiles.isEmpty())
    {
        int cost = 0;
        Tile * currentTile = tiles.dequeue(&cost);
        if(!currentTile->visited)
        {
            currentTile->visited = true;
            if (currentTile == maze->goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            auto successors = new Tile *[4]();
            maze->getSuccessors(currentTile->row, currentTile->col, successors);

            for (int i = 0; i < 4; i++) {
                if (successors[i] != nullptr && !successors[i]->visited) {
                    delete successors[i]->route;
                    successors[i]->route = new Queue<int>;
                    if (!currentTile->route->isEmpty()) {
                        currentTile->route->copyQueue(successors[i]->route);
                    }

                    successors[i]->route->enqueue(i);
                    int totalCost = currentTile->route->size() + euclidean_distance(successors[i], maze->goalTile);
                    tiles.enqueue(successors[i], totalCost);
                }
            }
            delete[] successors;
        }
    }
    maze->resetVisitedTiles();
}

int Search::euclidean_distance(Tile *a, Tile *b) {
    int distance = (int) sqrt((pow(a->row - b->row,2)) + (pow(a->col - b->col,2)));
    return distance;
}
