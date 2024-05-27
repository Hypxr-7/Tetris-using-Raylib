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
               distribution(0, 6),
               scores(LoadScores()){
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
    UpdateScore();
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

void Game::DrawInfoDisplay() {
    DrawRectangle(screenWidth, 0, infoDisplayWidth, screenHeight, DARKBLUE);

    // display for next block
    DrawTextEx(font, "NEXT BLOCK", {static_cast<float>(screenWidth + 30), 20}, 25, 1, RAYWHITE);
    DrawRectangle(screenWidth + 40, 80, 120, 120, GRAY);

    // drawing next block
    for (auto item : nextBlock.blockCells[nextBlock.rotationState])
        DrawRectangle(screenWidth + 40 + int(item.x) * 30, 80 + int(item.y) * 30, 30, 30, nextBlock.color);

    // display for high scores
    DrawTextEx(font, "HIGH SCORES", {static_cast<float>(screenWidth + 25), 240}, 25, 1, RAYWHITE);
    DrawRectangle(screenWidth + 40, 280, 120, 120, GRAY);

    // displaying high scores from vector
    for (int i = 0; i < 3; ++i)
        DrawTextEx(font, scores[i].c_str(), {static_cast<float>(screenWidth + 45), static_cast<float>(280 + 40 * i)}, 25, 1, RAYWHITE);


    DrawTextEx(font, "SCORE", {static_cast<float>(screenWidth + 40), 400}, 25, 1, RAYWHITE);
    DrawRectangle(screenWidth + 40, 440, 120, 40, GRAY);
    std::string temp = std::to_string(grid.scores);
    DrawTextEx(font, temp.c_str(), {static_cast<float>(screenWidth + 40), 440}, 25, 1, RAYWHITE);
}

std::vector<std::string> Game::LoadScores() {
    std::ifstream fileHandle{"assets/highscores/scores.txt"};
    assert(fileHandle.is_open() && "File not Found");

    std::vector<std::string> vec;
    for (int i = 0; i < 3; ++i){
        std::string line;
        std::getline(fileHandle, line);
        vec.push_back(line);
    }
    fileHandle.close();

    return vec;
}

void Game::UpdateScore() {
    scores.push_back(std::to_string(grid.scores));
    std::ranges::sort(scores, [](const auto& a, const auto& b){ return a > b; });

    std::ofstream fileHandle{"assets/highscores/scores.txt"};
    for (int i = 0; i < 3; ++i)
        fileHandle << scores[i] << '\n';

    fileHandle.close();
}

