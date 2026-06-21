#pragma once
#include <iostream>
#include <algorithm>
namespace jtodd{
    class Square{
        public:
        Square(const int k_adjacentMines);
        int Reveal();
        void Flag();
        void Print(bool ShowBombs);
        bool IsRevealed();

        bool IsMine();
        bool IsFlagged();

        private:
        const int k_adjacentMines; // 0 means none, 1-8 means some, and 9 means it IS a mine.
        bool m_revealed; //whether or not the square has been revealed by the user.
        bool m_flagged;  //whether or not the square has been flagged as a mine by the user.

    };
};