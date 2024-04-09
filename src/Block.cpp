#include "Block.h"

Block::Block(int id_, int s) : id(id_), rotationState(0), cellSize(s) {
    // x = column and y = row for this class

    assert(id >= 1 && id <= 7);  // invalid ID passed

    if (id == 1) { // O block
        blockCells[0] = {{0, 0},{0, 1},{1, 0},{1, 1}};
        position = {4, 0};
        color = {255, 255, 0, 255};
    }

    if (id == 2){ // I block
        blockCells[0] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
        blockCells[1] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
        position = {3, 0};
        color = {0, 255, 255, 255};
    }

    if (id == 3){ // S block
        blockCells[0] = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
        blockCells[1] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
        position = {4, 0};
        color = {255, 0, 0, 255};
    }


    if (id == 4){ // Z block
      blockCells[0] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
      blockCells[1] = {{1, 0}, {1, 1}, {0, 1}, {0, 2}};
      position = {4, 0};
      color = {0, 255, 0, 255};
    }

    if (id == 5){ // L block
        blockCells[0] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
        blockCells[1] = {{0, 1}, {1, 1}, {2, 1}, {2, 0}};
        blockCells[2] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
        blockCells[3] = {{0, 2}, {0, 1}, {1, 1}, {2, 1}};
        position = {4, 0};
        color = {255, 128, 0, 255};
    }

    if (id == 6){ // J block
        blockCells[0] = {{1, 0}, {1, 1}, {1, 2}, {0, 2}};
        blockCells[1] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
        blockCells[2] = {{2, 0}, {1, 0}, {1, 1}, {1, 2}};
        blockCells[3] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
        position = {4 ,0};
        color = {255, 51, 153, 255};
    }

    if (id == 7){ // T block
        blockCells[0] = {{0, 1}, {1, 1}, {2, 1}, {1, 2}};
        blockCells[1] = {{1, 0}, {1, 1}, {1, 2}, {0, 1}};
        blockCells[2] = {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
        blockCells[3] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
        position = {4, 0};
        color = {204, 0, 204, 255};
    }
}

void Block::Draw() {
    std::vector<Vector2> tiles = blockCells[rotationState];
    for (Vector2 currentCell : tiles)
        DrawRectangle((position.x + currentCell.x) * cellSize + 1, (position.y + currentCell.y) * cellSize + 1, cellSize - 1, cellSize - 1, color);
}

std::vector<Vector2> Block::GetLowestCell() {
    int currentLowest = -1;

    for (auto cell : blockCells[rotationState])
        if (cell.y > currentLowest)
            currentLowest = cell.y;

    std::vector<Vector2> temp;
    for (auto cell : blockCells[rotationState])
        if (cell.y == currentLowest)
            temp.push_back(cell);

    return temp;
}
