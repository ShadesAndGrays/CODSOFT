#include <cctype>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>



void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}


enum PROBLEM{
    NONE,
    NAN,
    TOOBIGG,
    UNKNOWN
};
void angryMessage(PROBLEM cause){
    static int angryCounter = 0;

    auto lessThanTwo = [](int x){return x < 2;};
    auto lessThanFive= [](int x){return x < 5;};
    auto lessThanTen= [](int x){return x < 10;};

    switch (cause) {
        case NONE:
            angryCounter = 0;
            break;
        case NAN:
            if(lessThanTwo(angryCounter))
                std::cout<< "Really?"<< std::endl;
            else if(lessThanFive(angryCounter))
                std::cout<< "Are you even trying? >:("<< std::endl;
            else if(lessThanTen(angryCounter))
                std::cout<< "Come on Take this seriously <:`("<< std::endl;
            angryCounter++;
            break;
        case TOOBIGG:
            if(lessThanTwo(angryCounter))
                std::cout<< "I am not reading that "<< std::endl;
            else if(lessThanFive(angryCounter))
                std::cout<< "How many numbers is that even"<< std::endl;
            else if(lessThanTen(angryCounter))
                std::cout<< "I am suprised you are still playing !("<< std::endl;
            angryCounter++;
            break;
        default:
            for (auto i = 0; i < angryCounter+1; i++)
                std::cout << "?";
            std::cout<<std::endl;;
            angryCounter++;
            break;
    }

}
int main() {

    clearScreen();
    std::cout << "Welcome to the guessing game" << std::endl;
    bool isPlaying = true;
    int difficulty = 1;
    while (isPlaying){
        int randomNumber = rand() % (10 * difficulty * 2) - (10 * difficulty);

        std::cout << "Try an guess my number :)" << std::endl;

        while (true) {
            std::string choice = "";
            std::cout << ":";
            std::cin >> choice;
            clearScreen();

            int choiceInt = 0; 
            try{
                choiceInt = std::stoi(choice);
                angryMessage(PROBLEM::NONE);
            }catch(std::invalid_argument){
                angryMessage(PROBLEM::NAN);
                continue;
            }catch(std::out_of_range){
                angryMessage(PROBLEM::TOOBIGG);
                continue;
            }catch(std::exception e){
                angryMessage(PROBLEM::UNKNOWN);
                continue;
            }


            if(choiceInt == randomNumber){
                std::cout << "Yay!! you got it :) the number was indeed " << randomNumber << std::endl; 
                break;
            }
            else if(abs(choiceInt - randomNumber) == 1){
                std::cout << "You are so close you would not even belive it :)" << std::endl;
            }
            else if (abs(choiceInt - randomNumber) == 3){
                std::cout << "You are getting warmer" << std::endl;
            }
            else if (choiceInt >  randomNumber){
                std::cout << "The number is Lower that that" << std::endl;
            } 
            else if (choiceInt <  randomNumber){
                std::cout << "The number is Higher than that" << std::endl;
            } 
            else{
                std::cout << "what was that?" <<std::endl; 
            }
        }

        while (true){
            std::cout << "Would you like to play again:";
            std::string choice;
            std::cin >> choice;
            bool badChoice = false;
            badChoice |= choice.length() != 1;
            if (badChoice){
                std::cout << "Sorry what ?";
            }

            if ( std::tolower(choice[0]) == 'n' ){
                std::cout << "Alright see you next time >:)";
                isPlaying = false;
                break;
            }
            else if ( std::tolower(choice[0]) == 'y' ){
                std::cout << "Yay GoodLuck. I am making it harder now >:)";
                difficulty++;
                break;
            }
        }
        clearScreen();
    }
    // std::cout << "Hi Dad!" << std::endl;
}
