#include "Grid.h"

Grid::Grid(int r, int c, int s) : rows(r), columns(c), cellSize(s){
    for (int i = 0; i < rows; ++i) {
        std::vector<int> temp;
        for (int j = 0; j < columns; ++j) {
            temp.push_back(0);
        }
        grid.push_back(temp);
    }

    colors.push_back({0, 0, 70, 255});
    colors.push_back({255, 255, 0, 255});
    colors.push_back({0, 255, 255, 255});
    colors.push_back({255, 0, 0, 255});
    colors.push_back({0, 255, 0, 255});
    colors.push_back({255, 128, 0, 255});
    colors.push_back({255, 51, 153, 255});
    colors.push_back({204, 0, 204, 255});
}

void Grid::Draw() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            DrawRectangle(j * cellSize + 1, i * cellSize + 1, cellSize - 1, cellSize - 1, colors[grid[i][j]]);
}

void Grid::ClearRows() {
    int completedRows = 0;
    for (int i = rows - 1; i >= 0; --i){
        if (IsRowFull(i)){
            completedRows++;
            ClearRow(i);
        }
        else if (completedRows > 0){
            MoveRowsDown(i, completedRows);
        }
    }
}

bool Grid::IsRowFull(int row) {
    for (int j = 0; j < columns; ++j){
        if (grid[row][j] == 0){
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (int j = 0; j < columns; ++j){
        grid[row][j] = 0;
    }
}

void Grid::MoveRowsDown(int row, int amount) {
    for (int j = 0; j < columns; ++j){
        grid[row + amount][j] = grid[row][j];
        grid[row][j] = 0;
    }
}
