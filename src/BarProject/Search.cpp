//
// Created by Alvarado, Alejandro on 5/27/17.
//
#include <math.h>
#include "Search.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "HashMap.h"

void Search::dfs(Tile* startTile, Tile* goalTile, Queue<int> * route)
{
    HashMap<char*> * visited = new HashMap<char*>();
    char * value; *value = 'v';
    Stack <Tile *> tiles;
    tiles.push(startTile);
    while(!tiles.isEmpty())
    {
        Tile * currentTile = tiles.pop();
        if(visited->get(currentTile->key.c_str()) == nullptr) {
            visited->put(currentTile->key.c_str(), value);
            if (currentTile == goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            auto successors = new Tile *[4]();
            //maze->getSuccessors(currentTile->row, currentTile->col, successors);

            for (int i = 0; i < 4; i++) {
                if (successors[i] != nullptr && visited->get(successors[i]->key.c_str()) == nullptr) {
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
    delete visited;
}

void Search::bfs(Tile* startTile, Tile* goalTile, Queue<int> * route)
{
    HashMap<char*> * visited = new HashMap<char*>();
    char * value; *value = 'v';
    Queue <Tile *> tiles;
    tiles.enqueue(startTile);
    while(!tiles.isEmpty())
    {
        Tile * currentTile = tiles.dequeue();
        if(visited->get(currentTile->key.c_str()) == nullptr)
        {
            visited->put(currentTile->key.c_str(), value);
            if (currentTile == goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            auto successors = new Tile *[4]();
            //maze->getSuccessors(currentTile->row, currentTile->col, successors);

            for (int i = 0; i < 4; i++) {
                if (successors[i] != nullptr && visited->get(successors[i]->key.c_str()) == nullptr) {
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
    delete visited;
}

void Search::astar(Tile* startTile, Tile* goalTile, Queue<int> *route) {
    HashMap<char*> * visited = new HashMap<char*>();
    char * value; *value = 'v';
    PriorityQueue<Tile *> tiles;
    tiles.enqueue(startTile, euclidean_distance(startTile, goalTile));
    while(!tiles.isEmpty())
    {
        int cost = 0;
        Tile * currentTile = tiles.dequeue(&cost);
        if(visited->get(currentTile->key.c_str()) == nullptr)
        {
            visited->put(currentTile->key.c_str(), value);
            if (currentTile == goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            auto successors = new Tile *[4]();
           //maze->getSuccessors(currentTile->row, currentTile->col, successors);

            for (int i = 0; i < 4; i++) {
                if (successors[i] != nullptr && visited->get(successors[i]->key.c_str()) == nullptr) {
                    delete successors[i]->route;
                    successors[i]->route = new Queue<int>;
                    if (!currentTile->route->isEmpty()) {
                        currentTile->route->copyQueue(successors[i]->route);
                    }

                    successors[i]->route->enqueue(i);
                    int totalCost = currentTile->route->size() + euclidean_distance(successors[i], goalTile);
                    tiles.enqueue(successors[i], totalCost);
                }
            }
            delete[] successors;
        }
    }
    delete visited;
}

int Search::euclidean_distance(Tile *a, Tile *b) {
    int distance = (int) sqrt((pow(a->row - b->row,2)) + (pow(a->col - b->col,2)));
    return distance;
}
