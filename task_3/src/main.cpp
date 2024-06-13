#include <cctype>
#include <cstdlib>
#include <exception>
#include <thread>
#include <iostream>
#include <string>
#include <vector>


enum TURN{
    X_TURN,
    O_TURN,
};
// will occupy a tile on the grid
enum ELEMENT{
    NONE,
    X,
    O
};

// Our little state machine is over here
struct GameState{
    std::vector<ELEMENT> board;
    TURN currentTurn;
    bool gameOver;
    ELEMENT winner;
    bool PVP;
};

// setting defualts of game state.
GameState initialzeGame(){
    GameState gameState;
    for (auto i = 0;i < 9; i++){
        gameState.board.push_back(ELEMENT::NONE);
    }
    gameState.currentTurn = TURN::X_TURN;
    gameState.gameOver = false;
    gameState.winner = ELEMENT::NONE;
    gameState.PVP = true;

    return gameState;
}

void displayBoard(GameState& state,bool intro = false){
    for(auto i = 0; i< 7; i++){
        std::cout << "-";
    }
    std::cout <<std::endl;
    for (auto i = 0; i < 9; i++){

        std::cout  << "|" ;
        switch (state.board[i]) {
            case X:
                std::cout << "X";
                break;
            case O:
                std::cout << "O";
                break;
            case NONE:
                // display numbers if displayin intro grid
                std::cout << (intro ? std::to_string(i+1) : " ");
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

    // starting positon of each winning startegy
    std::vector<int> vWins {0,1,2};
    std::vector<int> hWins {0,3,6};
    std::vector<int> dWins{2,0}; // positon swap to take advantage of indexing in for loop

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
            return;
        }
        oWon &= state.board[i] == ELEMENT::O;
        oWon &= state.board[i+3] == ELEMENT::O;
        oWon &= state.board[i+6] == ELEMENT::O;
        if (oWon)
        {
            state.winner = ELEMENT::O;
            state.gameOver = true;
            return;
        }
    }
    // Checking for all wins from left to right in O(n)
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
            return;
        }
        oWon &= state.board[i] == ELEMENT::O;
        oWon &= state.board[i+1] == ELEMENT::O;
        oWon &= state.board[i+2] == ELEMENT::O;
        if (oWon)
        {
            state.winner = ELEMENT::O;
            state.gameOver = true;
            return;
        }
    }
    // Check for diagonal wins
    for (auto i = 0; i < dWins.size(); i++){

        bool xWon = true;
        bool oWon = true;
        // std::cout << dWins[i] << " " << dWins[i] + (i*2) + 2 << " " << dWins[i] + (i*4) + 4 << std::endl;
        xWon &= state.board[dWins[i]] == ELEMENT::X;
        xWon &= state.board[dWins[i] + (i*2) + 2] == ELEMENT::X;
        xWon &= state.board[dWins[i] + (i*4) + 4] == ELEMENT::X;
        if (xWon)
        {
            state.winner = ELEMENT::X;
            state.gameOver = true;
            return;
        }
        oWon &= state.board[dWins[i]] == ELEMENT::O;
        oWon &= state.board[dWins[i] + (i*2) + 2] == ELEMENT::O;
        oWon &= state.board[dWins[i] + (i*4) + 4] == ELEMENT::O;
        if (oWon)
        {
            state.winner = ELEMENT::O;
            state.gameOver = true;
            return;
        }

    }

    bool draw = true;
    for (auto i : state.board){
        // check if there are no more empty spots
        draw &= i != ELEMENT::NONE;
    }
    if (draw){
        state.winner = ELEMENT::NONE;
        state.gameOver = true;
    }
}

void playerPlay(GameState &state){
    using namespace std::chrono_literals;
    std::string input;
    while (true){

        std::cout << "Player " << (state.currentTurn == TURN::X_TURN? "X" : "O") << " Enter input: ";
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
            switch(state.currentTurn){
                case X_TURN:
                    state.board[position] = ELEMENT::X;
                    break;
                case O_TURN:
                    state.board[position] = ELEMENT::O;
                    break;
            }
            break;

        } catch (std::exception e) {
            std::cerr << "Enter position within 1-9" << std::endl;

        }
    }
    // Pause for dramatic effect
    std::this_thread::sleep_for(500ms);
}

void computerPlay(GameState &state){
    using namespace std::chrono_literals;
    std::cout << "Computer" << std::endl;
    while(true){
        int pos = std::rand() % 8 ;
        std::cout << pos << std::endl;
        if (state.board[pos] == ELEMENT::NONE){
            state.board[pos] = ELEMENT::O;
            break;
        }
    }
    std::this_thread::sleep_for(500ms);
}
int main() {

    GameState game = initialzeGame();

    std::string single;
    bool pvp;
    std::cout << "Playing against Another Player?(y/n): ";
    while (true){
        std::getline(std::cin,single);
        if (single.length() > 1){
            std::cout << "(y / n)?" << std::endl;
            continue;
        }
        if (tolower(single[0]) == 'y'){
            pvp = true;
            break;

        }
        else if (tolower(single[0]) == 'n'){
            pvp = false;
            break;
        }
        else{
            std::cout << "(y / n)?" << std::endl;
            continue;
        }
    }


    while(true){
        displayBoard(game,true);
        while(!game.gameOver){
            switch (game.currentTurn) {
                case X_TURN:
                    playerPlay(game);
                    displayBoard(game);
                    game.currentTurn = TURN::O_TURN;
                    break;
                case O_TURN:
                    if (pvp)
                        playerPlay(game);
                    else
                        computerPlay(game);
                    displayBoard(game);
                    game.currentTurn = TURN::X_TURN;
                    break;
            };
            checkEnd(game);
        }
        switch (game.winner) {
            case X:
                std::cout << "Winner was X" << std::endl;
                break;
            case O:
                std::cout << "Winner was O" << std::endl;
                break;
            case NONE:
                std::cout << "Game was a draw";
                break;
        }

        std::string playAgain;
        std::cout << "Woule you like to play again(y/n): " ;
        while (true){
            std::getline(std::cin,playAgain);
            if (playAgain.length() > 1){
                std::cout << "(y / n)?" << std::endl;
                continue;
            }
            if (tolower(playAgain[0]) == 'y'){
                std::cout << "Next Round " << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                game = initialzeGame();
                break;
            }
            else if (tolower(playAgain[0]) == 'n'){
                std::cout << "Thx for playing >:) " << std::endl;
                return 0;
            }
            else{
                std::cout << "(y / n)?" << std::endl;
                continue;
            }
        }
    }

    return 0;
}
