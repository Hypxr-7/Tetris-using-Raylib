#ifndef TETRIS_USING_RAYLIB_BLOCK_H
#define TETRIS_USING_RAYLIB_BLOCK_H

#include <raylib.h>
#include <vector>
#include <map>
#include <cassert>

class Block {
private:
    int cellSize;
public:
    int id;
    Color color;
    Vector2 position;
    int rotationState;
    std::map<int, std::vector<Vector2>> blockCells;

    Block(int id, int s);
    void Draw();
};


#endif //TETRIS_USING_RAYLIB_BLOCK_H
