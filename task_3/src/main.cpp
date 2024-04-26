#include <iostream>
#include <vector>

enum TURN{
    X_TURN,
    O_TURN,
};

enum CAPTURE{
    NONE,
    X,
    O
};

struct GameState{
    std::vector<CAPTURE> board;
    TURN currentTurn;
};

GameState initialzeGame(){
    GameState gameState;
    for (auto i = 0;i < 9; i++){
        gameState.board.push_back(CAPTURE::NONE);
    }
    gameState.currentTurn = TURN::X_TURN;

    return gameState;
}

void displayBoard(GameState& state){
    for(auto i = 0; i< 7; i++){
        std::cout << "-";
    }
    std::cout <<std::endl;
    for (auto i = 0; i < 9; i++){

        std::cout  << "|" << "x";
        if ((i+1) %3 == 0){
            std::cout <<"|";
            std::cout << std::endl;
        }
    }
    for(auto i = 0; i< 7; i++){
        std::cout << "-";
    }

}

int main() {
    GameState game = initialzeGame();
    displayBoard(game);

}
