#include <exception>
#include <iostream>
#include <sstream>
#include <vector>
// I am going to use a stack data structure to make it fancy

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
            stream << "]"  << std::endl;
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

};

class Calculator{

    private:
        // memory cells to hold tempoary values
        
        double mem1,mem2,mem3;
        Stack stack; 
    public:
        Calculator(){}

};


int main() {
    Stack stack;
    stack.push(12.1);
    stack.push(22.4);
    stack.displayStack();
    stack.push(1.2);
    stack.push(53.5);
    stack.displayStack();


}
