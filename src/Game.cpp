#include "Game.h"

// TODO : Add UI for next Block
// TODO : Add logic and UI for score counting
// TODO : Add SFX
// TODO: Add high score tracker

Game::Game() : cellSize(30),
               rows(20),
               columns(10),
               infoDisplayWidth(200),
               grid(rows, columns, cellSize) ,
               blockIDList({1, 2, 3, 4, 5, 6, 7}),
               currentBlock(InitializeBlock()),
               nextBlock(InitializeBlock()),
               interval(600),
               randomGenerator(std::random_device{}()),
               distribution(0, 6) {
    screenWidth = cellSize * columns;
    screenHeight = cellSize * rows;
    lastCall = std::chrono::steady_clock::now();
    InitWindow(screenWidth + infoDisplayWidth, screenHeight, "Tetris");
    InitAudioDevice();
    music = LoadMusicStream("assets/bgm/bgm-track-1.mp3");
    font = LoadFontEx("assets/fonts/SpaceMono.ttf", 64, nullptr, 0);

    SetTargetFPS(30);
}

Game::~Game() {
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}

void Game::Run() {
    PlayMusicStream(music);
    while (!WindowShouldClose()){
        Update();
        BeginDrawing();
        Draw();
        EndDrawing();
    }
}

void Game::Update() {
    UpdateMusicStream(music);
    if (IsKeyPressed(KEY_UP)) Rotate();
    if (IsKeyPressed(KEY_LEFT)) MoveLeft();
    if (IsKeyPressed(KEY_RIGHT)) MoveRight();
    LockBlock();
    if (IsKeyDown(KEY_DOWN)) MoveDown();
    if (CheckElapsedTime()) MoveDown();
    grid.ClearRows();
}

void Game::Draw() {
    ClearBackground(GRAY);

    DrawInfoDisplay();
    grid.Draw();
    currentBlock.Draw();
}

Block Game::InitializeBlock() {
    if (blockIDList.empty()) blockIDList = {1, 2, 3, 4, 5, 6, 7};

    distribution = std::uniform_int_distribution<int>(0, int(blockIDList.size() - 1));

    int index = distribution(randomGenerator);
    Block block(blockIDList[index], cellSize);
    blockIDList.erase(blockIDList.begin() + index);

    return block;
}

void Game::Rotate() {
    currentBlock.rotationState++;
    if (currentBlock.rotationState > currentBlock.blockCells.size() - 1) currentBlock.rotationState = 0;

    if (OutOfBounds() || BottomReached()){
        if (currentBlock.rotationState == 0) currentBlock.rotationState = int(currentBlock.blockCells.size()) - 1;
        else currentBlock.rotationState--;
    }
}

bool Game::OutOfBounds() {
    return std::ranges::any_of(currentBlock.blockCells[currentBlock.rotationState], [this](const auto& item) {
        return currentBlock.position.x + item.x < 0 || currentBlock.position.x + item.x > columns - 1;
    });
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

bool Game::CheckElapsedTime() {
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
        grid.grid[int(item.y + currentBlock.position.y)][int(item.x + currentBlock.position.x)] = currentBlock.id;
    }
}

bool Game::BottomReached() {
     return std::ranges::any_of(currentBlock.blockCells[currentBlock.rotationState], [this](const auto& item){
        return item.y + currentBlock.position.y >= rows - 1;
    });
}

bool Game::BlockOverlaps() {
    return std::ranges::any_of(currentBlock.blockCells[currentBlock.rotationState], [this](const auto& item){
        return grid.grid[item.y + 1 + currentBlock.position.y][item.x + currentBlock.position.x] != 0;
    });

}

void Game::DrawInfoDisplay() const {
    DrawRectangle(screenWidth, 0, infoDisplayWidth, screenHeight, DARKBLUE);



    DrawTextEx(font, "NEXT BLOCK", {static_cast<float>(screenWidth + 40), 20}, 25, 1, RAYWHITE);
    DrawRectangle(screenWidth + 40, 80, 120, 120, GRAY);

//    for (auto item : nextBlock.blockCells){
//        Vector2 posn = item.second;
    }
}

