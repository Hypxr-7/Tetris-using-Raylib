#ifndef TETRIS_USING_RAYLIB_LAUNCHER_H
#define TETRIS_USING_RAYLIB_LAUNCHER_H

#include <raylib.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

struct Info{
    float rows;
    float columns;
    float cellSize;
    float speed;
};

class Launcher {
private:
    Info* info;
    Texture texture;
    Font font;
    bool defaultRows;
    bool defaultColumns;
    bool defaultCellSize;
    bool defaultSpeed;

    void Draw() {
        DrawTexture(texture, 0, 0, RAYWHITE);

        DrawTextEx(font, "Default", {10, 20}, 30, 1, RAYWHITE);

        DrawTextEx(font, "Rows [15-40]", {350, 20}, 30, 1, RAYWHITE);
        GuiCheckBox((Rectangle){10, 57, 57, 57}, nullptr, &defaultRows);
        if (defaultRows) {
            DrawRectangle(250, 57, 400, 57, GRAY);
            DrawTextEx(font, "20", {700, 57}, 40, 1, RAYWHITE);
            info->rows = 20;
        }
        else {
            GuiSliderBar((Rectangle) {250, 57, 400, 57}, nullptr, nullptr, &info->rows, 15, 40);
            info->rows = int(info->rows);
            DrawTextEx(font, std::to_string(int(info->rows)).c_str(), {700, 57}, 40, 1, RAYWHITE);
        };

        DrawTextEx(font, "Columns [10, 50]", {350, 134}, 30, 1, RAYWHITE);
        GuiCheckBox((Rectangle){10, 171, 57, 57}, nullptr, &defaultColumns);
        if (defaultColumns) {
            DrawRectangle(250, 171, 400, 57, GRAY);
            DrawTextEx(font, "10", {700, 171}, 40, 1, RAYWHITE);
            info->columns = 10;
        }
        else {
            GuiSliderBar((Rectangle) {250, 171, 400, 57}, nullptr, nullptr, &info->columns, 10, 50);
            info->columns = int(info->columns);
            DrawTextEx(font, std::to_string(int(info->columns)).c_str(), {700, 171}, 40, 1, RAYWHITE);
        };

        DrawTextEx(font, "Cell Size [10, 50]", {350, 248}, 30, 1, RAYWHITE);
        GuiCheckBox((Rectangle){10, 285, 57, 57}, nullptr, &defaultCellSize);
        if (defaultCellSize) {
            DrawRectangle(250, 285, 400, 57, GRAY);
            DrawTextEx(font, "30", {700, 285}, 40, 1, RAYWHITE);
            info->cellSize = 30;
        }
        else {
            GuiSliderBar((Rectangle) {250, 285, 400, 57}, nullptr, nullptr, &info->cellSize, 10, 50);
            info->cellSize = int(info->cellSize);
            DrawTextEx(font, std::to_string(int(info->cellSize)).c_str(), {700, 285}, 40, 1, RAYWHITE);
        };

        DrawTextEx(font, "Speed [500, 700]", {350, 362}, 30, 1, RAYWHITE);
        GuiCheckBox((Rectangle){10, 399, 57, 57}, nullptr, &defaultSpeed);
        if (defaultSpeed) {
            DrawRectangle(250, 399, 400, 57, GRAY);
            DrawTextEx(font, "600", {700, 399}, 40, 1, RAYWHITE);
            info->speed = 600;
        }
        else {
            GuiSliderBar((Rectangle) {250, 399, 400, 57}, nullptr, nullptr, &info->speed, 500, 700);
            info->speed = int(info->speed);
            DrawTextEx(font, std::to_string(int(info->speed)).c_str(), {700, 399}, 40, 1, RAYWHITE);
        };

    }

public:
    Launcher(Info* infoPtr) : defaultRows(false), defaultCellSize(false), defaultColumns(false), defaultSpeed(false) {
        info = infoPtr;
        info->rows = 20;
        info->columns = 10;
        info->cellSize = 30;
        info->speed = 600;
        InitWindow(900, 506, "Launcher");
        SetTargetFPS(60);
        Image image = LoadImage("assets/images/bg.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        font = LoadFont("assets/fonts/SpaceMono.ttf");
//        GuiSetFont(font);
//        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    }

    ~Launcher() {
        UnloadTexture(texture);
        UnloadFont(font);
        CloseWindow();
    }

    void Run() {
        while (!WindowShouldClose()) {
            BeginDrawing();
            Draw();
            EndDrawing();
        }
    }
};


#endif //TETRIS_USING_RAYLIB_LAUNCHER_H
