#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

std::string input(std::string prompt);
void clearScreen();

class OptionGetter{
    private:
        std::vector<std::function<void()>> options;
        int currentOption;
    public:
        OptionGetter(){
            currentOption = 0;
        }
        OptionGetter prompt(std::string prompt){
            std::cout << "prompt" << std::endl;
            return *this;
        }
        OptionGetter addOption(std::string optionString,std::function<void()> func){
            this->currentOption ++;
            this->options.push_back(func);
            std::cout <<currentOption <<". "<< optionString << std::endl;
            return *this;
        }
        void run(){
            while (true){
                try {
                    int choice =  std::stoi(input("Enter option: "));
                    if (choice > this->options.size() || choice <=  0 )
                        throw std::exception();
                    options[choice -1]();
                    break;
                } catch (std::exception e) {
                    std::cout << "Invalid Option" << std::endl;
                }
            }
        }

};

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

std::string input(std::string prompt){
    std::cout << prompt;
    std::string value;
    std::getline(std::cin,value);
    return value;
}



int main() {

    clearScreen();
    std::cout << "Welcome to ToDo" << std::endl;
    OptionGetter OG;
    OG.prompt("Which is the best color")
        .addOption("Red",[](){std::cout << "Red is a nice colour but no"  << std::endl;})
        .addOption("Blue",[](){std::cout << "Now we are taling >:) Blue is awesome"  << std::endl;})
        .addOption("Green",[](){std::cout << "Really ?? Green :|"  << std::endl;})
        .run();





}
