#include "game.hpp"
#include <ctime>
int main(){

    int MineAmount;
    int Width;
    int Height;
    std::string option;

    std::cout<<"\n\n          ---===MINESWEEPER===---\n\n";
    while (true){
        std::cout<<"\nPlease select one of the following Presets:\n\n   Easy(9x9, 10 mines)\n   Normal(16x16, 40 mines)\n   Hard(30x16, 99 mines)\n\n";
        std::cin>>option;
        if (option == "Easy"){
            MineAmount = 10;
            Width = 9;
            Height = 9;
            break;
        }
        if (option == "Normal"){
            MineAmount = 40;
            Width = 16;
            Height = 16;
            break;
        }
        if (option == "Hard"){
            MineAmount = 99;
            Width = 30;
            Height = 16;
            break;
        }
        std::cout<<"\nThat is not one of the options; try again.\n";
    }

    jtodd::Game g(MineAmount, Width, Height);
    while (!g.getGameOver()){
        g.Print(false);
        g.ReadCommand();
        if (g.CheckWin()){
            std::cout<<"\n\n---===VICTORY===---\n\n";
            break;
        }
    }
    
    return 0;
}
