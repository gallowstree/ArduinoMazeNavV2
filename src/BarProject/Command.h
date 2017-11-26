#ifndef MAZENAV_COMMAND_H
#define MAZENAV_COMMAND_H

#include "Tile.h"

#define UNDEFINED '0'
#define MAP_MAZE '1'
#define SEARCH '2'
#define PARSE_MAP '3'
#define SET_IP '4'

#define DFS 'D'
#define BFS 'B'
#define ASTAR 'A'

class Command {
    
        public:
            Command();
            char type;
            String startTile;
            String goalTile;
            String serverIP;
            char searchAlg;
            void parseCommand(String data);   
    };
    
#endif 