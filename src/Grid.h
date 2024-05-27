#ifndef TETRIS_USING_RAYLIB_GRID_H
#define TETRIS_USING_RAYLIB_GRID_H

#include <raylib.h>
#include <vector>
#include <map>
#include <raymath.h>

class Grid {
private:
    int rows;
    int columns;
    int cellSize;

    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowsDown(int row, int amount);
public:
    int scores;
    std::vector<Color> colors;
    std::vector<std::vector<int>> grid;

    Grid(int r, int c, int s);
    void Draw();
    void ClearRows();
};


#endif //TETRIS_USING_RAYLIB_GRID_H
