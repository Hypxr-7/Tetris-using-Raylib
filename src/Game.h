#ifndef TETRIS_USING_RAYLIB_GAME_H
#define TETRIS_USING_RAYLIB_GAME_H

#include <raylib.h>
#include <random>
#include <chrono>
#include <vector>
#include <ranges>
#include <string>
#include <algorithm>
#include <fstream>
#include "Block.h"
#include "Grid.h"

#include <iostream>

class Game {
private:
    int cellSize;
    int rows;
    int columns;
    int screenWidth;
    int screenHeight;
    int infoDisplayWidth;
    std::chrono::steady_clock::time_point lastCall;
    int interval;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<int> distribution;
    Grid grid;
    std::vector<int> blockIDList;
    Block currentBlock;
    Block nextBlock;
    std::vector<std::string> scores;

    Music music;
    Font font;

    Block InitializeBlock();
    void Rotate();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    bool CheckElapsedTime();
    bool OutOfBounds();
    void LockBlock();
    bool BottomReached();
    bool BlockOverlaps();
    void AddBlockToGrid();
    void DrawInfoDisplay();
    std::vector<std::string> LoadScores();
    void Draw();
    void Update();
public:
    Game();
    ~Game();
    void Run();
};

#endif //TETRIS_USING_RAYLIB_GAME_H
