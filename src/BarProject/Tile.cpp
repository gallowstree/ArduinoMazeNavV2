//
// Created by Alvarado, Alejandro on 4/15/17.
//

#include "Tile.h"

Tile::Tile()
{
    route = new Queue<int>();
}

Tile::~Tile() {
    delete route;
}
