#include <exception>
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

void checkEnd(GameState &state){
    // Handling end game logic
/*  
    0 1 2
    3 4 5
    6 7 8
 *  */

    //  All possible win strategies 
    // const std::vector<std::vector<int>> wins{{0,3,6},{1,4,7},{2,5,8},{0,1,2},{3,4,8},{6,7,8}, {0,4,8},{2,5,8}};

    std::vector<int> vWins {0,1,2};
    std::vector<int> hWins {0,3,6};
    std::vector<int> dWins{2,0};

    // Checking for all wins from top to button in O(n)
    for (auto i : vWins){
        bool xWon = true;
        bool oWon = true;
        // std::cout << i << " " << i + 3 << " " << i + 6 << std::endl;
        xWon &= state.board[i] == ELEMENT::X;
        xWon &= state.board[i+3] == ELEMENT::X;
        xWon &= state.board[i+6] == ELEMENT::X;
        if (xWon)
        {
            state.winner = ELEMENT::X;
            state.gameOver = true;
            break;
        }
        oWon &= state.board[i] == ELEMENT::O;
        oWon &= state.board[i+3] == ELEMENT::O;
        oWon &= state.board[i+6] == ELEMENT::O;
        if (oWon)
        {
            state.winner = ELEMENT::O;
            state.gameOver = true;
            break;
        }
    }
    // Checking for all wins from top to button in O(n)
    for (auto i : hWins){
        bool xWon = true;
        bool oWon = true;
        // std::cout << i << " " << i + 3 << " " << i + 6 << std::endl;
        xWon &= state.board[i] == ELEMENT::X;
        xWon &= state.board[i+1] == ELEMENT::X;
        xWon &= state.board[i+2] == ELEMENT::X;
        if (xWon)
        {
            state.winner = ELEMENT::X;
            state.gameOver = true;
            break;
        }
        oWon &= state.board[i] == ELEMENT::O;
        oWon &= state.board[i+1] == ELEMENT::O;
        oWon &= state.board[i+2] == ELEMENT::O;
        if (oWon)
        {
            state.winner = ELEMENT::O;
            state.gameOver = true;
            break;
        }
    }
    for (auto i = 0; i < dWins.size(); i++){

        bool xWon = true;
        bool oWon = true;
         std::cout << dWins[i] << " " << dWins[i] + (i*2) + 2 << " " << dWins[i] + (i*4) + 4 << std::endl;
        xWon &= state.board[dWins[i]] == ELEMENT::X;
        xWon &= state.board[dWins[i] + (i*2) + 2] == ELEMENT::X;
        xWon &= state.board[dWins[i] + (i*4) + 4] == ELEMENT::X;
        if (xWon)
        {
            state.winner = ELEMENT::X;
            state.gameOver = true;
            break;
        }
        oWon &= state.board[dWins[i]] == ELEMENT::O;
        oWon &= state.board[dWins[i] + (i*2) + 2] == ELEMENT::O;
        oWon &= state.board[dWins[i] + (i*4) + 4] == ELEMENT::O;
        if (oWon)
        {
            state.winner = ELEMENT::O;
            state.gameOver = true;
            break;
        }

    }

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
    std::this_thread::sleep_for(1000ms);

}
void computerPlay(GameState state){
    using namespace std::chrono_literals;
    std::cout <<  "Computer played " << std::endl;
    std::this_thread::sleep_for(1000ms);

}
int main() {

    GameState game = initialzeGame();

    while(!game.gameOver){

        displayBoard(game);
        switch (game.currentTurn) {
            case X_TURN:
                playerPlay(game);
            case O_TURN:
                computerPlay(game);
        };
        checkEnd(game);
    }
    switch (game.winner) {
        case X:
            std::cout << "Winner was X";
            break;
        case O:
            std::cout << "Winner was O";
            break;
        case NONE:
            std::cout << "Game was a draw";
            break;
    }

}
