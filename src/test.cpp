#include "Launcher.h"
#include <iostream>

int main(){
    Info info;
    {
        Launcher launcher(&info);
        launcher.Run();
    }
    std::cout << info.rows << " " << info.columns << ' ' << info.cellSize << ' ' << info.speed << '\n';


    return 0;
}