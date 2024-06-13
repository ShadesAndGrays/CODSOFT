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
        std::string optionText;
        int currentOption;
    public:
        OptionGetter(){
            currentOption = 0;
        }

        OptionGetter prompt(std::string prompt){

            std::cout <<"\n"<< prompt << std::endl;
            return *this;
        }
        // yes and no questions 
        bool binaryPrompt(std::string prompt){
            std::cout << prompt << "(y/n): ";
            while (true){
                std::string input;
                std::getline(std::cin,input);
                if(input.size() > 1){
                    std::cout << "(y/n)? ";
                }else if(std::tolower(input[0]) == 'y'){
                    return true;
                }else if(std::tolower(input[0]) == 'n'){
                    return false;
                }
            }
        }

        OptionGetter addOption(std::string optionString,std::function<void()> func){
            this->currentOption++;
            this->options.push_back(func);
            this->optionText +=  std::to_string(currentOption) + ". " + optionString + "\n";
            return *this;

        }
        void run(){
            std::cout << this->optionText;
            while (true){
                try {
                    int choice =  std::stoi(input("Enter option: "));
                    if (choice > this->options.size() || choice <=  0 )
                        throw std::exception();
                    clearScreen();
                    options[choice -1]();
                    break;
                } catch (std::exception e) {
                    std::cout << "Invalid Option" << e.what()<< std::endl;
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
                Task(){}
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
                std::cout << "It is pretty empty here (\'>\')" << std::endl;
                std::cout << "Try adding some tasks " << std::endl;
                return;
            }
            auto Opt = OptionGetter();
            for (Task &i :this->taskList){
                std::cout << "[" <<(i.taskCompleted ? "X": " ") <<"] ";
                std::cout << i.taskName << std::endl;
                Opt.addOption(i.taskName, [i](){std::cout << i.taskName<<"::: \n-> "<< i.taskDescription << std::endl;});
            }
            Opt.addOption("Exit", [](){});
            Opt.prompt("view description:");
            Opt.run();

        }

        void updateTask(){
            bool updating = true;
            auto allTaskCompleted = [&](){
                bool complete = true;
                for (Task &i :this->taskList){
                    complete &= i.taskCompleted;
                }
                if (complete)
                    std::cout << "All task done !! \\('3')/ !! " << std::endl;
            };
            while (updating){
                allTaskCompleted();
                auto Opt = OptionGetter();
                for (Task &i :this->taskList){
                    std::cout << "[" <<(i.taskCompleted ? "X": " ") <<"] ";
                    std::cout << i.taskName << std::endl;
                    Opt.addOption(i.taskName, [&i](){i.taskCompleted = !i.taskCompleted;});
                }
                Opt.addOption("Exit", [&](){updating = false;});
                Opt.prompt("Status Change");
                Opt.run();
            }
        }

        void addTask(){
            Task task;
            while(true){
                std::string name =input("Task Name: "); 
                std::string desc = input("Task Descrption: ");
                task = Task(name,desc);
                bool isCorrect = OptionGetter().binaryPrompt("Is this correct");
                if(isCorrect){
                    break;
                }
            }
            taskList.push_back(task);
        }

        void removeTask(){
            OptionGetter Opt; 
            for (int i = 0; i < this->taskList.size(); i++){
                std::cout << "[" <<(this->taskList[i].taskCompleted ? "X": " ") <<"] ";
                std::cout << this->taskList[i].taskName << std::endl;
                Opt.addOption(this->taskList[i].taskName, [&,i](){
                        bool remove = OptionGetter().binaryPrompt("Are you sure you want to delete " + this->taskList[i].taskName); 
                        if (remove){
                        this->taskList.erase(this->taskList.begin() + i);
                        }
                        });
            }
            Opt.addOption("Exit", [](){});
            Opt.prompt("Remove Task");
            Opt.run();
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
    TaskManager taskManger;

    bool running = true;
    while(running) {
        OptionGetter()
            .prompt("To Do Operations")
            .addOption("View Task",[&](){taskManger.displayTask();})
            .addOption("Change Task status",[&](){taskManger.updateTask();})
            .addOption("Add Task",[&](){taskManger.addTask();})
            .addOption("Remove Task",[&](){taskManger.removeTask();})
            .addOption("Exit",[&](){std::cout << "Thank you for using ToDo >:)" << std::endl; running = false;})
            .run();
    }





}
