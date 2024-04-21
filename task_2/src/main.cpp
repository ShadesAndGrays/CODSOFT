#include <exception>
#include <functional>
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
                    value = 0;
                    operate(add);
                    break;
                case SUBTRACT:
                    value = reverseStack.pop();
                    operate(sub);
                    break;
                case MULTIPLY:
                    value = 1;
                    operate(mul);
                    break;
                case DIVIDE:
                    value = reverseStack.pop();
                    operate(div);
                    break;
                case NEGATE:
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
        void clear(){
            while(stack.size() > 0){
                stack.pop();
            }
        }
        void store(MEM mem){
            if (this->stack.size() == 1){
                switch (mem) {
                    case MEM1:
                        this->mem1 = this->stack.peek();
                        break;
                    case MEM2:
                        this->mem2 = this->stack.peek();
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


int main() {
    Calculator calc;
    for (auto i = 0; i < 20; i ++)
        calc.addNumber(i);
    calc.squash(Calculator::NEGATE);




}
