
#include "Maze.h"

Tile* Maze::getTileAt(int row, int col)const {
    return &this->tiles[row][col];
}

Maze::Maze(int rows, int cols) : cols(cols),
                                       rows(rows)
{
    this->tiles = new Tile*[rows]();

    for (int r = 0; r < rows; r++)
    {
        this->tiles[r] = new Tile[cols]();
        for (int c = 0; c < cols; c++)
        {
            Tile* t = new Tile();
            t->row = r;
            t->col = c;

            t->hasWallAt[DIRECTION_UP] = r == 0;
            t->hasWallAt[DIRECTION_DOWN] = r == rows - 1;
            t->hasWallAt[DIRECTION_LEFT] = c == 0;
            t->hasWallAt[DIRECTION_RIGHT] = c == cols - 1;

//            bool hasWall = r == rows - 1 && c == 0;
//            t->hasWallAt[DIRECTION_UP] = hasWall;
//            t->hasWallAt[DIRECTION_DOWN] = hasWall;
//            t->hasWallAt[DIRECTION_LEFT] = hasWall;
//            t->hasWallAt[DIRECTION_RIGHT] = hasWall;


            tiles[r][c] = *t;
        }
    }
}

Maze::~Maze() {
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            //delete getTileAt(r, c);
        }
        delete[] tiles[r];
    }
    delete[] tiles;

}

int Maze::getRows()const {
    return this->rows;
}


int Maze::getCols()const {
    return this->cols;
}

int Maze::getSuccessors(int row, int col, Tile* result[]) const {

    if ( row < 0 || col < 0 || row >= rows || col >= cols )
        return -1;

    int successorCount = 0;

    Tile* t = getTileAt(row, col);

    if (!t->hasWallAt[DIRECTION_LEFT] && col > 0) {
        result[DIRECTION_LEFT] = getTileAt(row, col - 1);
        successorCount++;
    }

    if (!t->hasWallAt[DIRECTION_UP] && row > 0) {
        result[DIRECTION_UP] = getTileAt(row - 1, col);
        successorCount++;
    }

    if (!t->hasWallAt[DIRECTION_RIGHT] && col < cols - 1) {
        result[DIRECTION_RIGHT] = getTileAt(row, col + 1);
        successorCount++;
    }

    if (!t->hasWallAt[DIRECTION_DOWN] && row < rows - 1) {
        result[DIRECTION_DOWN] = getTileAt(row + 1, col);
        successorCount++;
    }

    return successorCount;
}

void Maze::resetVisitedTiles()
{
    for(int row = 0; row < this->rows; row++)
    {
        for(int col = 0; col < this->cols; col++)
        {
            Tile * tile = this->getTileAt(row,col);
            tile->visited = false;
            delete tile->route;
            tile->route = new Queue<int>;
        }
    }
}

