#include "Game.h"

// TODO : Add UI for next Block
// TODO : Add logic and UI for score counting
// TODO : Add BGM and SFX
Game::Game() : cellSize(30), rows(20), columns(10), grid(rows, columns, cellSize) , blockIDList({1, 2, 3, 4, 5, 6, 7}), currentBlock(InitializeBlock()),
               nextBlock(InitializeBlock()){
    screenWidth = cellSize * columns;
    screenHeight = cellSize * rows;
    lastCall = std::chrono::steady_clock::now();
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(30);
}

Game::~Game() {
    CloseWindow();
}

void Game::Run() {
    while (!WindowShouldClose()){
        Update();
        BeginDrawing();
        Draw();
        EndDrawing();
    }
}

void Game::Update() {
    if (IsKeyPressed(KEY_UP)) Rotate();
    if (IsKeyPressed(KEY_LEFT)) MoveLeft();
    if (IsKeyPressed(KEY_RIGHT)) MoveRight();
    LockBlock();
    if (IsKeyDown(KEY_DOWN)) MoveDown();
    if (CheckElapsedTime(600)) MoveDown();
    grid.ClearRows();
}

void Game::Draw() {
    ClearBackground(GRAY);

    grid.Draw();
    currentBlock.Draw();
}

Block Game::InitializeBlock() {
    if (blockIDList.empty()) blockIDList = {1, 2, 3, 4, 5, 6, 7};

    int index = rand() % blockIDList.size();
    Block block(blockIDList[index], cellSize);
    blockIDList.erase(blockIDList.begin() + index);

    return block;
}

void Game::Rotate() {
    currentBlock.rotationState++;
    if (currentBlock.rotationState > currentBlock.blockCells.size() - 1) currentBlock.rotationState = 0;

    if (OutOfBounds()){
        if (currentBlock.rotationState == 0) currentBlock.rotationState = currentBlock.blockCells.size() - 1;
        else currentBlock.rotationState--;
    }
}

bool Game::OutOfBounds() {
    for (const auto& item : currentBlock.blockCells[currentBlock.rotationState])
        if (currentBlock.position.x + item.x < 0 || currentBlock.position.x + item.x > columns - 1)
            return true;

    return false;
}

void Game::MoveRight() {
    currentBlock.position.x++;
    if (OutOfBounds() || BlockOverlaps()) currentBlock.position.x--;
}

void Game::MoveLeft() {
    currentBlock.position.x--;
    if (OutOfBounds() || BlockOverlaps()) currentBlock.position.x++;
}

void Game::MoveDown() {
    currentBlock.position.y++;
}

bool Game::CheckElapsedTime(int interval) {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCall).count();
    if (elapsedTime > interval){
        lastCall = currentTime;
        return true;
    }
    return false;
}

void Game::LockBlock() {
    if (BottomReached() || BlockOverlaps()){
        AddBlockToGrid();
        currentBlock = nextBlock;
        nextBlock = InitializeBlock();

    }
}

void Game::AddBlockToGrid() {
    for (auto item : currentBlock.blockCells[currentBlock.rotationState]) {
        grid.grid[item.y + currentBlock.position.y][item.x + currentBlock.position.x] = currentBlock.id;
    }
}

bool Game::BottomReached() {
    for (auto item : currentBlock.blockCells[currentBlock.rotationState]){
        if (item.y + currentBlock.position.y >= rows - 1) return true;
    }
    return false;
}

bool Game::BlockOverlaps() {
    for (auto item : currentBlock.blockCells[currentBlock.rotationState]){
        item.y++;
        if (grid.grid[item.y + currentBlock.position.y][item.x + currentBlock.position.x] != 0){
            return true;
        }
    }
    return false;
}

