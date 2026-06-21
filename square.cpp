#include "square.hpp"

namespace jtodd{
    Square::Square(const int k_adjacentMines) : k_adjacentMines(k_adjacentMines), m_revealed(false), m_flagged(false){}

    int Square::Reveal(){
        m_revealed = true;
        if (k_adjacentMines == 9) //9 adjacent mines is code for is a mine, so if it is a mine, then return 2 to stop the process and say game over.
            return 2;
        if (k_adjacentMines > 0)
            return 1;// stop the revealing process
        return 0; // continue the revealing process
    }
    bool Square::IsRevealed(){
        return m_revealed;
    }
    void Square::Flag(){
        m_flagged = !m_flagged;
    }
    void Square::Print(bool showBombs){
        if (showBombs && k_adjacentMines == 9){
            std::cout<<" B ";
            return;
        }
        if (m_flagged){
            std::cout<<" F ";
            return;
        }
        if (!m_revealed){
            std::cout<<"[] "; //blank square
            return;
        }
        if (k_adjacentMines == 0){
            std::cout<<"   "; //no mines, true blank square
            return;
        }
        std::cout<<' '<<k_adjacentMines<<' '; //number of adjacent mines
    }
    bool Square::IsMine(){
        return k_adjacentMines == 9;
    }
    bool Square::IsFlagged(){
        return m_flagged;
    }
};