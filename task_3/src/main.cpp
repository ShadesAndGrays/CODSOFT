#include <exception>
#include <functional>
#include <thread>
#include <iostream>
#include <string>
#include <vector>


enum TURN{
    X_TURN,
    O_TURN,
};

enum ELEMENT{
    NONE,
    X,
    O
};

struct GameState{
    std::vector<ELEMENT> board;
    TURN currentTurn;
    bool gameOver;
    ELEMENT winner;
};

GameState initialzeGame(){
    GameState gameState;
    for (auto i = 0;i < 9; i++){
        gameState.board.push_back(ELEMENT::NONE);
    }
    gameState.currentTurn = TURN::X_TURN;
    gameState.gameOver = false;
    gameState.winner = ELEMENT::NONE;

    return gameState;
}

void displayBoard(GameState& state){
    for(auto i = 0; i< 7; i++){
        std::cout << "-";
    }
    std::cout <<std::endl;
    for (auto i = 0; i < 9; i++){
        
        std::cout  << "|" ;
        switch (state.board[i]) {
            case NONE:
                std::cout << " ";
                break;
            case X:
                std::cout << "X";
                break;
            case O:
                std::cout << "O";
                break;

        }
        if ((i+1) %3 == 0){
            std::cout <<"|";
            std::cout << std::endl;
        }
    }
    for(auto i = 0; i< 7; i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

bool gameEnded(GameState &state){
    
    bool xWon = true;
    bool oWon = true;
/*  
    0 1 2
    3 4 5
    6 7 8
 *  */

    // const std::vector<std::vector<int>> wins{{0,3,6},{1,4,7},{2,5,8},{0,1,2},3,4,8};
    std::vector<int> vWins {0,1,2};
    std::vector<int> hWins {0,3,6};

    for (auto i : vWins){
        xWon &= state.board[i] == X;
        xWon &= state.board[i+3] == X;
        xWon &= state.board[i+6] == X;
        if (xWon)
        {
            state.winner = ELEMENT::X;
            state.gameOver = true;
        }
        oWon &= state.board[i] == O;
        oWon &= state.board[i+3] == O;
        oWon &= state.board[i+6] == O;
        if (oWon)
        {
            state.winner = ELEMENT::O;
            state.gameOver = true;
        }
    }



    return false;
}

void playerPlay( GameState &state){

    using namespace std::chrono_literals;
    std::string input;
    while (true){

        std::cout <<  "Enter input: ";
        std::getline(std::cin,input);
        try {
            int position = std::stoi(input) -1;
            if(position < 0 || position >= state.board.size()){
                std::cerr << "Enter position within 1-9" << std::endl;
                continue;
            }
            if (state.board[position] != ELEMENT::NONE){
                std::cerr << "Space already taken" << std::endl;
                continue;
            }
            state.board[position] = ELEMENT::X;
            break;

        } catch (std::exception e) {
            std::cerr << "Enter position within 1-9" << std::endl;

        }
    }
    std::cout <<  "Player played " << input << std::endl;
    std::this_thread::sleep_for(2000ms);

}
void computerPlay(GameState state){
    using namespace std::chrono_literals;
    std::cout <<  "Computer played " << std::endl;
    std::this_thread::sleep_for(2000ms);

}
int main() {


    GameState game = initialzeGame();

    int x = 0;

    while(!game.gameOver){

        displayBoard(game);
        switch (game.currentTurn) {
            case X_TURN:
                playerPlay(game);
            case O_TURN:
                 computerPlay(game);
        };
        gameEnded(game);



    }

}
