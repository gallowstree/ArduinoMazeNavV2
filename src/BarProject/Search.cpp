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
    Stack <Tile *> tiles;
    tiles.push(startTile);
    while(!tiles.isEmpty())
    {
        Tile * currentTile = tiles.pop();
        if(visited->get(currentTile->key.c_str()) == nullptr) {
            visited->put(currentTile->key.c_str(), visitedValue);
            if (currentTile == goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }


            for (int i = 0; i < 4; i++) {
                Tile * currentSuccesor = currentTile->successors[i];
                if (currentSuccesor != nullptr && visited->get(currentSuccesor->key.c_str()) == nullptr) {
                    delete currentSuccesor->route;
                    currentSuccesor->route = new Queue<int>;
                    if (!currentTile->route->isEmpty()) {
                        currentTile->route->copyQueue(currentSuccesor->route);
                    }

                    currentSuccesor->route->enqueue(i);
                    tiles.push(currentSuccesor);
                }
            }
        }
    }
    delete visited;
}

void Search::bfs(Tile* startTile, Tile* goalTile, Queue<int> * route)
{
    HashMap<char*> * visited = new HashMap<char*>();
    Queue <Tile *> tiles;
    tiles.enqueue(startTile);
    while(!tiles.isEmpty())
    {
        Tile * currentTile = tiles.dequeue();
        if(visited->get(currentTile->key.c_str()) == nullptr)
        {
            visited->put(currentTile->key.c_str(), visitedValue);
            if (currentTile == goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            

            for (int i = 0; i < 4; i++) {
                Tile * currentSuccesor = currentTile->successors[i];
                if (currentSuccesor != nullptr && visited->get(currentSuccesor->key.c_str()) == nullptr) {
                    delete currentSuccesor->route;
                    currentSuccesor->route = new Queue<int>;
                    if (!currentTile->route->isEmpty()) {
                        currentTile->route->copyQueue(currentSuccesor->route);
                    }

                    currentSuccesor->route->enqueue(i);
                    tiles.enqueue(currentSuccesor);
                }
            }
        }
    }
    delete visited;
}

void Search::astar(Tile* startTile, Tile* goalTile, Queue<int> *route) {
    HashMap<char*> * visited = new HashMap<char*>();
    PriorityQueue<Tile *> tiles;
    tiles.enqueue(startTile, euclidean_distance(startTile, goalTile));
    while(!tiles.isEmpty())
    {
        int cost = 0;
        Tile * currentTile = tiles.dequeue(&cost);
        if(visited->get(currentTile->key.c_str()) == nullptr)
        {
            visited->put(currentTile->key.c_str(), visitedValue);
            if (currentTile == goalTile) {
                currentTile->route->copyQueue(route);
                break;
            }

            for (int i = 0; i < 4; i++) {
                Tile * currentSuccesor = currentTile->successors[i];
                if (currentSuccesor != nullptr && visited->get(currentSuccesor->key.c_str()) == nullptr) {
                    delete currentSuccesor->route;
                    currentSuccesor->route = new Queue<int>;
                    if (!currentTile->route->isEmpty()) {
                        currentTile->route->copyQueue(currentSuccesor->route);
                    }

                    currentSuccesor->route->enqueue(i);
                    int totalCost = currentTile->route->size() + euclidean_distance(currentSuccesor, goalTile);
                    tiles.enqueue(currentSuccesor, totalCost);
                }
            }
        }
    }
    delete visited;
}

int Search::euclidean_distance(Tile *a, Tile *b) {
    int distance = (int) sqrt((pow(a->row - b->row,2)) + (pow(a->col - b->col,2)));
    return distance;
}
