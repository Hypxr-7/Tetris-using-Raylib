#include "Game.h"
#include "Launcher.h"

int main(){
    Info info;
    {
        Launcher launcher(&info);
        launcher.Run();
    }

    Game game(info.rows, info.columns, info.cellSize, info.speed);
    game.Run();

    return 0;
}

