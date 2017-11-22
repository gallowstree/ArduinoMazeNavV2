//
// Created by Alvarado, Alejandro on 4/15/17.
//

#include "Tile.h"
#include "Arduino.h" //To use string and generate the key

Tile::Tile(int row, int col) : row(row), col(col) {
    key = String(row);
    key.concat(",");
    key.concat(col);       
    route = new Queue<int>();
}

Tile::~Tile() {
    Serial.println("deleting tile");
    delete route;
}
