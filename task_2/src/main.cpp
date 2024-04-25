#include <exception>

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// I am going to use a stack data structure to make it fancy

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

class StackUnderFlow : public std::exception{
    virtual const char * what() const throw(){
        return "Stack size is Zero (0)";

    }

};

class Stack{

    private:
        std::vector<double> array;

    public:
        Stack(){}
        void displayStack(){
            std::cout << "[";
            for (auto i = 0; i < array.size() ; i++){
                std::cout << array[i];
                if (i != array.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]"  << std::endl;
        }

        std::string toString(){
            std::stringstream stream;
            stream << "[";
            for (auto i = 0; i < array.size() ; i++){
                stream << array[i];
                if (i != array.size() - 1)
                    stream << ", ";
            }
            stream << "]";
            return stream.str();
        }


        void push(double number){
            array.push_back(number);
        }
        double pop() {
            if(array.size() <= 0){
                throw StackUnderFlow();
            }
            double value = *(array.end() -1);
            array.pop_back();
            return value;
        }
        double peek(){
            return *(array.end() - 1);
        }
        size_t size(){
            return array.size();
        }

};

class Calculator{

    private:
        // memory cells to hold tempoary values
        double mem1,mem2,mem3;
        Stack stack; 
    public:
        enum OPERATION{
            ADD,
            SUBTRACT,
            MULTIPLY,
            DIVIDE,
            NEGATE,
        };
        enum MEM{
            MEM1,
            MEM2,
            MEM3
        };
        Calculator(){}
        void squash(OPERATION op){
            double value = 0;
            Stack reverseStack;
            while (stack.size() > 0){
                reverseStack.push(stack.pop());
            }
            auto add = [](double ls,double rs){return ls + rs;};
            auto sub = [](double ls,double rs){return ls - rs;};
            auto div = [](double ls,double rs){return ls / rs;};
            auto mul = [](double ls,double rs){return ls * rs;};
            auto neg = [](double val){return -1 * val;};
            auto operate = [&](std::function<double(double ls, double rs)> operation){
                while (reverseStack.size() > 0){
                    value = operation(value, reverseStack.pop());
                }
                stack.push(value);
            };
            auto transform = [&](std::function<double(double ls)> operation){
                while (reverseStack.size() > 0){
                    value = operation(reverseStack.pop());
                    stack.push(value);
                }
            };
            switch (op) {
                case ADD:
                    std::cout << "Stack: " << stack.toString() << " Op: " << "ADD" << std::endl;
                    value = 0;
                    operate(add);
                    break;
                case SUBTRACT:
                    std::cout << "Stack: " << stack.toString() << " Op: " << "SUB" << std::endl;
                    value = reverseStack.pop();
                    operate(sub);
                    break;
                case MULTIPLY:
                    std::cout << "Stack: " << stack.toString() << " Op: " << "MUL" << std::endl;
                    value = 1;
                    operate(mul);
                    break;
                case DIVIDE:
                    std::cout << "Stack: " << stack.toString() << " Op: " << "DIV" << std::endl;
                    value = reverseStack.pop();
                    operate(div);
                    break;
                case NEGATE:
                    std::cout << "Stack: " << stack.toString() << " Op: " << "NEG" << std::endl;
                    value = -1;
                    transform(neg);
                    break;
            }
            stack.displayStack();
        }
        void addNumber(double num){
            stack.push(num);
            stack.displayStack();
        }
        void removeLast(){
            stack.pop();
            stack.displayStack();
        }
        void clear(){
            while(stack.size() > 0){
                stack.pop();
            }
            this->mem1 = this->mem2 = this->mem3 = 0;
            view();
        }
        void view(){
            stack.displayStack();
        }
        void store(MEM mem){
            if (this->stack.size() == 1){
                switch (mem) {
                    case MEM1:
                        this->mem1 = this->stack.peek();
                        break;
                    case MEM2: this->mem2 = this->stack.peek();
                               break;
                    case MEM3:
                               this->mem3 = this->stack.peek();
                               break;
                }

            }
            else if (this->stack.size() <= 0){
                std::cerr << "Error: stack is empty" << std::endl;
            }

            else{
                std::cout << "You must squash before storing" << std::endl;
            }
            stack.displayStack();
        }

        double getMem(MEM mem){
            switch (mem) {
                case MEM1:
                    return mem1;
                    break;
                case MEM2:
                    return mem2;
                    break;
                case MEM3:
                    return mem3;
                    break;
            }
            return 0.0;

        }
        void retrieve(MEM mem){
            switch (mem) {
                case MEM1:
                    this->stack.push(mem1);
                    break;
                case MEM2:
                    this->stack.push(mem2);
                    break;
                case MEM3:
                    this->stack.push(mem3);
                    break;
            }
            stack.displayStack(); 

        }


};

std::string input(std::string prompt){
    std::cout << prompt;
    std::string in;
    std::getline(std::cin, in);
    return in;
}


void inputCycle (Calculator& calc){
    std::cout << "'e' to exit   'u' to undo" << std::endl;
    std::string in = "";
    while(in != "e"){
        in = input("AddNumber::");
        try {
            if (in == "u"){
                calc.removeLast();
                continue;
            }
            calc.addNumber(std::stod(in));
        } catch (std::exception e) {
            if (in != "e")
                std::cout << "enter a valid number" << std::endl;
            continue;
        }
    }
}

void processSquash(Calculator &calc){
    std::stringstream option;
    option << "0. exit\n";
    option << "1. addition\t";
    option << "2. subtract\t";
    option << "3. multiply\t";
    option << "4. divide\t";
    option << "5. negate\t";
    std::cout << option.str()  << std::endl;
    while (true){
        std::string choice = input("Sqush:: ");
        int choiceInt = 0;
        int x = 0;
        try {
            x = std::stoi(choice);
        }catch(std::exception e){
            std::cout << "enter a valid option" << std::endl;
        }
        switch (x) {
            case 0:
                return;
            case 1:
                calc.squash(Calculator::ADD);
                return;
            case 2:
                calc.squash(Calculator::SUBTRACT);
                return;
            case 3:
                calc.squash(Calculator::MULTIPLY);
                return;
            case 4:
                calc.squash(Calculator::DIVIDE);
                return;
            case 5:
                calc.squash(Calculator::NEGATE);
                return;
            default:
                std::cout << "enter a valid option" << std::endl;
                std::cout << option.str() << std::endl;
                break;
        }
    }
}

void alterMem(Calculator &calc){
    std::stringstream option;
    option << "0. Exit\n";
    option << "1. View Mem Cell\t";
    option << "2. Push Cell To Stack\t";
    option << "3. Set Mem Cell\t";

    std::cout << option.str() << std::endl;
    auto displayCells = [&](){
        std::cout <<"Mem1: "<< calc.getMem(Calculator::MEM::MEM1) << " ";
        std::cout <<"Mem2: "<< calc.getMem(Calculator::MEM::MEM2) << " ";
        std::cout <<"Mem3: "<< calc.getMem(Calculator::MEM::MEM3) << " ";
        std::cout << std::endl;
    };
    auto numToMem = [](int num){
        switch (num) {
            case 1:
                return Calculator::MEM1;
                break;
            case 2:
                return Calculator::MEM2;
                break;
            case 3:
                return Calculator::MEM3;
                break;
            default:
                return Calculator::MEM1;
                break;
        }
    };

    while (true){
        std::string choice = input("Mem:: ");
        int choiceInt = 0;
        try {
            choiceInt = std::stoi(choice);
        }catch(std::exception e){
            choiceInt = -1;
        }

        switch (choiceInt) {
            case 0:
                // exiting
                return;
            case 1:
                displayCells();
                break;

            case 2:
                try {
                    int memCellNumber = std::stoi(input("Enter CellNumber: ")); 
                    calc.retrieve(numToMem(memCellNumber));
                }catch(std::exception e){
                    std::cout<< "Invalid Cell!" << std::endl;
                }
                displayCells();
                break;
            case 3:
                displayCells();
                try {

                    int memCellNumber = std::stoi(input("Enter CellNumber: ")); 
                    calc.store(numToMem(memCellNumber));
                }catch(std::exception e){
                    std::cout<< "Invalid Cell!" << std::endl;
                }
                break;
            default:
                std::cout << "Invalid Option!" << std::endl;
                std::cout << option.str() << std::endl;
                break;
        }
    }
}



int main() {
    Calculator calc;
    bool calculating = true;
    clearScreen();
    std::cout << "Welcome to Stackulator" << std::endl;
    input("Enter any key to continue:: ");
    clearScreen();

    calc.clear();
    std::stringstream option;
    option << "h. help\n";
    option << "c. clear screen\n";
    option << "0. exit\n";
    option << "1. view stack\n";
    option << "2. squash (+ | - | * | /)\n";
    option << "3. add number\n";
    option << "4. memory cell\n";
    option << "5. clear stack\n";

    std::string optionChoice; 
    int optionChoiceInt; // Integer makes it easier to parse
    std::cout  << option.str() << std::endl;
    while (calculating){
        optionChoice = input("Menu:: ");
        if (optionChoice == "h"){
            std::cout << option.str() << std::endl;
            continue;
        }
        else if (optionChoice == "c") {
            clearScreen();
            continue;
        }
        try {
            optionChoiceInt = std::stoi(optionChoice);
        } catch (std::exception e) {
            std::cerr << "Invalid Option!!! "<< std::endl;
            std::cout << option.str() << std::endl;
            continue;
        }

        switch (optionChoiceInt) {
            case 0:
                calculating = false;
                break;
            case 1:
                calc.view();
                break;
            case 2:
                processSquash(calc);
                break;
            case 3:
                inputCycle(calc);
                break;
            case 4:
                alterMem(calc);
                break;
            case 5:
                calc.clear();
                break;
            default:
                std::cerr << "Invalid Option!!! " << optionChoiceInt << std::endl;
                std::cout << option.str() << std::endl;
                continue;
        }
    }
    calc.clear();
    clearScreen();
    std::cout << "Thank you for using Stackulator" << std::endl;


}
