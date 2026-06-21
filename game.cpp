#include "game.hpp"
namespace jtodd{
    Game::Game(const int k_mineAmount, const int k_width, const int k_height) : k_mineAmount(k_mineAmount), k_width(k_width), k_height(k_height), m_gameOver(false){
        if (k_mineAmount > k_width * k_height){
            std::cout<<"FATAL ERROR; More Mines than spaces."; //there cannot be more mines than spaces (thx claude)
            return;
        }
        srand(time(NULL));
        for(int i = 0; m_Mines.size() < k_mineAmount ; ++i){
            int a = rand() % k_height; //find a random height
            int b = rand() % k_width;  //find a random width
            std::pair<int,int> c{a,b}; //make a std::pair of those values
            if (std::find(m_Mines.begin(), m_Mines.end(), c) == m_Mines.end()) //as long as std::find can't find the pair in the m_Mines vector, we push_back the std::pair
                m_Mines.push_back(c);
        }
        for (int i = 0 ; i < k_height ; ++i){
            if (m_Board.size() <= i){
                std::vector<Square> a;
                m_Board.push_back(a);
            }
            for (int j = 0 ; j < k_width ; ++j){
                std::pair <int, int> b{i,j};
                if (std::find(m_Mines.begin(), m_Mines.end(), b) != m_Mines.end()){ //if it's a mine
                    Square c(9);
                    m_Board[i].push_back(c);
                    continue;
                }
                int mines = 0;
                std::pair<int,int> d[8];
                d[0] = {i+1,j}; 
                d[1] = {i+1, j+1}; 
                d[2] = {i, j+1};
                d[3] = {i-1, j};
                d[4] = {i-1, j-1};
                d[5] = {i, j-1};
                d[6] = {i-1, j+1};
                d[7] = {i+1, j-1}; //these are coords of all adjacent squares 
                if (i != k_width - 1){ //i+1
                    if (std::find(m_Mines.begin(), m_Mines.end(), d[0]) != m_Mines.end()) // j+0
                        ++mines;
                    if (j != k_height - 1 && std::find(m_Mines.begin(), m_Mines.end(), d[1]) != m_Mines.end()) //j+1
                        ++mines;
                    if (j != 0 && std::find(m_Mines.begin(), m_Mines.end(), d[7]) != m_Mines.end()) //j-1
                        ++mines;
                }


                if(i != 0){ //i-1
                    if (std::find(m_Mines.begin(), m_Mines.end(), d[3]) != m_Mines.end()) // j+0
                        ++mines;
                    if (j != k_height - 1 && std::find(m_Mines.begin(), m_Mines.end(), d[6]) != m_Mines.end()) //j+1
                        ++mines;
                    if (j != 0 && std::find(m_Mines.begin(), m_Mines.end(), d[4]) != m_Mines.end()) //j-1
                        ++mines;
                }

                //i+0
                    if (j != k_height - 1 && std::find(m_Mines.begin(), m_Mines.end(), d[2]) != m_Mines.end()) //j+1
                        ++mines;
                    if (j != 0 && std::find(m_Mines.begin(), m_Mines.end(), d[5]) != m_Mines.end()) //j-1
                        ++mines;
                
                Square e(mines);
                m_Board[i].push_back(e);
            }
        }
    }

    bool Game::getGameOver(){
        return m_gameOver;
    }

    void Game::Print(bool showBombs){
        std::cout<<"      ";
        for (int i = 1 ; i <= k_width ; ++i){
            if (i < 9)
                std::cout<<i<<"  ";
            else 
                std::cout<<i<<' ';
        }
        std::cout<<"\n\n";
        int a = 0;
        for (std::vector<Square> i : m_Board){
            if (++a >= 10)
                std::cout<<a<<"   ";
            else 
                std::cout<<a<<"    ";
            for (Square j : i)
                j.Print(showBombs); //Print all squares
            std::cout<<"\n";
        }
            
        
    }


    void Game::GameOver(){
        m_gameOver = true;
        std::cout<<"\n\n----====GAME OVER====----\n\n\n";
        Print(true);
        std::cout<<"\n\n\n";
    }


    void Game::ReadCommand(){
        
        while(true){
            std::string command;
            std::cout<<"\nEnter your command (type \"help\" or \"?\" for help):\n";
            std::cin>>command;
            if (command == "help" || command == "?"){
                std::cout<<"\n\"reveal\" followed by 2 numbers reveals a square:\n    reveal 12 27\n\"flag\" puts a flag at the specified coordinates:\n    flag 12 27\n";
                continue;
            }
            if (command == "reveal"){
                unsigned int x,y;
                if (!(std::cin >> x >> y)){
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');  // Remove bad input
                    std::cout << "\nInvalid coordinates. Please enter two coordinates.\n";
                    continue;
                }
                --x; --y; //so that more intuitive coords can be used
                if (x > k_width){
                    std::cout<<"\nInvalid x coordinate, try again.\n";
                    continue;
                }
                if (y > k_height){
                    std::cout<<"\nInvalid y coordinate, try again.\n";
                    continue;
                }
                ChainReveals(x,y);
                return;
            }
            if (command == "flag"){
                unsigned int x,y;
                if (!(std::cin >> x >> y)){
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');  // Remove bad input
                    std::cout << "\nInvalid coordinates. Please enter two coordinates.\n";
                    continue;
                }
                --x; --y; //so that more intuitive coords can be used
                if (x > k_width){
                    std::cout<<"\nInvalid x coordinate, try again.\n";
                    continue;
                }
                if (y > k_height){
                    std::cout<<"\nInvalid y coordinate, try again.\n";
                    continue;
                }
                m_Board[y][x].Flag();
                return;
            }
            std::cout<<"\nInvalid Command. Please try again\n";
            std::cin.ignore(2, '\n');
        }
    }
    void Game::ChainReveals(unsigned int x, unsigned int y){
        if (m_Board[y][x].Reveal() == 2){
            GameOver();
            return;
        }

        if (m_Board[y][x].Reveal() == 1)
            return;

        if (x != 0){
            if (!m_Board[y][x - 1].IsRevealed())
                ChainReveals(x - 1,y);
            if (y != 0)
                if (!m_Board[y - 1][x - 1].IsRevealed())
                    ChainReveals(x - 1, y - 1);
            if (y < k_height - 1)
                if (!m_Board[y + 1][x - 1].IsRevealed())
                    ChainReveals(x - 1, y + 1);
        }
        if (y != 0){
            if (!m_Board[y - 1][x].IsRevealed())
                ChainReveals(x,y - 1);
        }
        if (y < k_height - 1){
            if (!m_Board[y + 1][x].IsRevealed())
                ChainReveals(x,y + 1);
        }
        if (x < k_width - 1){
            if (!m_Board[y][x + 1].IsRevealed())
                ChainReveals(x + 1,y);

            if (y != 0){
                if (!m_Board[y - 1][x + 1].IsRevealed())
                    ChainReveals(x + 1,y - 1);
            }
            if (y < k_height - 1){
                if (!m_Board[y + 1][x + 1].IsRevealed())
                    ChainReveals(x + 1,y + 1);
            }
        }
        return;
    }
    bool Game::CheckWin(){
        for (std::vector<Square> i : m_Board){
            for (Square j : i){
                if (!j.IsMine() && (j.IsFlagged() || !j.IsRevealed()))
                    return false;
            }
        }
        return true;
    }
};