#include <cstring>
#include <database.hpp>
#include <memory>
#include <raylib.h>
#include <raygui.h>
#include <SearchPage.h>
#include <util.h>
#include <iostream>




void displayBooks(GuiSearchPageState &sp, std::shared_ptr<DatabaseManger> db){
    sp.elements.clear();
    std::string filter;
    switch (sp.searchFilter) {
        case TITLE:
            filter = "title";
            // std::cout << "Search By title" << std::endl;
            break;
        case ISBN:
            filter = "isbn";
            // std::cout << "Search By ISBN" << std::endl;
            break;
        case AUTHOR:
            filter = "author";
            // std::cout << "Search By Author" << std::endl;
            break;
    }
    std::vector <schema::Book> Books =  std::string(sp.SearchText) == "" ? db->getBooks() : db->getBooks(filter,"%" + std::string(sp.SearchText) + "%",false) ;


    for ( auto &i : Books){
        GuiBookElementState x = {0};
        strncpy(x.title, i.title.c_str(),128);
        strncpy(x.author, i.author.c_str(),128);
        strcpy(x.isbn, i.isbn.c_str());
        x.copies = i.noOfCopies;
        sp.elements.push_back(x);
    }

}


struct PopUpState{
    bool on;
    char title [32];
    char msg[128];
};
void popup(std::string title, std::string msg, PopUpState* popUpState){

    strncpy(popUpState->title, title.c_str(), sizeof(char) * 32);
    strncpy(popUpState->msg, msg.c_str(), sizeof(char) * 128);
    popUpState->on = true;
}
void GuiPopUp(PopUpState* popUpState){

    if (!popUpState->on)
        return;
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0,0,0,60});
    popUpState->on = !GuiWindowBox(scaleDynamic((Rectangle){SIZE_X/4.0 , SIZE_Y/4.0 ,300,300}), popUpState->title);
    GuiLabel(scaleDynamic((Rectangle){SIZE_X/4.0 + 100, SIZE_Y/4.0 ,300,300}),popUpState->msg);
}
int main() {
    auto db = DatabaseManger::getInstance();


    InitWindow(SIZE_X,SIZE_X,"BookKeeper");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    GuiSearchPageState sp = InitGuiSearchPage(); 

    Rectangle r1 {5,5,100,100};

    PopUpState ps {0};


    int i = 0;


    displayBooks(sp,db);
    while(!WindowShouldClose()){

        GuiSetStyle(DEFAULT,TEXT_SIZE, (float)GetScreenWidth()/SIZE_X * 11);
        GuiSetStyle(DEFAULT,TEXT_SPACING, (float)GetScreenWidth()/SIZE_X * 2);
        GuiSetStyle(DEFAULT,TEXTURE_FILTER_BILINEAR, 1);
        if (sp.Exit){
            break;
        }

        if(sp.SearchButtonPressed){
            displayBooks(sp,db);
            if (sp.elements.size() == 0)
                popup("Not Found", "The Book was found", &ps);
        }
        if (sp.checkOutBtn){
            auto books = std::vector<std::string> (sp.checkingOut.begin(),sp.checkingOut.end());
            db->borrowBook(books);
            sp.checkingOut.clear();

            sp.checkOutBtn = false;
            schema::printlogs(db->getBorrowLog());
        }

        if (IsKeyPressed(KEY_SPACE)){
            i = (i + 1) % 3;
        }


        BeginDrawing();
        // DrawRectangleRec(r1, Color{255,0,0,100});
        // DrawRectangleRec(scaleDynamic((Rectangle){0,0,SIZE_X,SIZE_Y}), Color{0,255,0,50});
        // DrawRectangleRec(scaleDynamic(r1), Color{0,0,255,100});

        ClearBackground(RAYWHITE);

        if(i == 0){
            GuiSearchPage(&sp);
        } else if(i == 1){
        }

        GuiPopUp(&ps);

        EndDrawing();

    }

}


