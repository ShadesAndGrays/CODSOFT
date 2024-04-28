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
            clearScreen();
            std::cout << prompt << std::endl;
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


class TaskManager{

    private:
        class Task{
            public:
            std::string taskName;
            std::string taskDescription;
            bool taskCompleted;
            Task(std::string name,std::string description): 
                taskName(name),
                taskDescription(description),
                taskCompleted(false){}
        };
        std::vector<Task> taskList;
    public:
        TaskManager(){}
        void displayTask(){
            if (taskList.size() == 0){

            std::cout << "It is pretty empty (\'>\')" << std::endl;
            std::cout << "Try adding some tasks " << std::endl;
            }
            for (Task i :this->taskList){
                std::cout << "[ " <<(i.taskCompleted ? "X": " ") <<" ]\t";
            }
        }
        void displayTask(int i){
            if (i > taskList.size()){

            }
            for (Task i :this->taskList){
                std::cout << "[ " <<(i.taskCompleted ? "X": " ") <<" ]\t";
                std::cout << ". "<< i.taskName << std::endl;
            }
        }
        void updateTask(){std::cout << "You have successully updated tasks\\('3')/" << std::endl;}
        void addTask(){
            Task task = Task(input("Task Name: "),input("Task Descrption: "));
            

        }
        void removeTask(){std::cout << "You have removed a task" << std::endl;}

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
    TaskManager taskManger;

    bool running = true;
    while(running) {
    OptionGetter()
        .prompt("To Do Operations")
        .addOption("Exit",[&](){running = false;})
        .addOption("View Task",[&](){taskManger.displayTask();})
        .addOption("Change Task status",[&](){taskManger.updateTask();})
        .addOption("Add Task",[&](){taskManger.addTask();})
        .addOption("Remove Task",[&](){taskManger.removeTask();})
        .run();
    }





}
