#pragma once
#include "square.hpp"
#include <vector>
namespace jtodd{
    class Game{
        public:
        Game(const int k_mineAmount, const int k_width, const int k_height);
        bool getGameOver();
        void Print(bool showBombs);
        void ReadCommand();
        bool CheckWin();
        
        private:
        std::vector<std::vector<Square>> m_Board;
        std::vector<std::pair<int,int>> m_Mines;
        const int k_width, k_height;
        const int k_mineAmount;
        bool m_gameOver;
        void GameOver();
        void ChainReveals(unsigned int x, unsigned int y);
    };
};