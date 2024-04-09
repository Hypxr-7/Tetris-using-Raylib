#ifndef TETRIS_USING_RAYLIB_GAME_H
#define TETRIS_USING_RAYLIB_GAME_H

#include <raylib.h>
#include <random>
#include <chrono>
#include <algorithm>
#include "Block.h"
#include "Grid.h"

class Game {
private:
    int cellSize;
    int rows;
    int columns;
    int screenWidth;
    int screenHeight;
    std::chrono::steady_clock::time_point lastCall;
//    int64_t elapsedTime;
    Grid grid;
    std::vector<int> blockIDList;
    Block currentBlock;
    Block nextBlock;
    Block InitializeBlock();
    void Rotate();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    bool CheckElapsedTime(int interval);
    bool OutOfBounds();
    void LockBlock();
    bool BottomReached();
    bool BlockOverlaps();
    void AddBlockToGrid();
    void Draw();
    void Update();
public:
    Game();
    ~Game();
    void Run();
};

#endif //TETRIS_USING_RAYLIB_GAME_H
