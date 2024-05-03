#include <cstring>
#include <database.hpp>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION 
#include <raygui.h>
#include <SearchPage.h>
#include <util.h>




int main() {
     auto db = DatabaseManger::getInstance();


    InitWindow(SIZE_X,SIZE_Y,"BookKeeper");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    GuiSearchPageState sp = InitGuiSearchPage(); 

    Rectangle r1 {5,5,100,100};


    int i = 0;
    while(!WindowShouldClose()){

        if (sp.Exit){
            break;
        }

        if(sp.SearchButtonPressed){
                sp.elements.clear();
                sp.SearchText;

            for ( auto i : db->getBooks()){
                GuiBookElementState x = {0};
                strncpy(x.title, i.title.c_str(),128);
                strncpy(x.author, i.author.c_str(),128);
                strcpy(x.isbn, i.isbn.c_str());
                x.copies = i.noOfCopies;
                sp.elements.push_back(x);

            }
        }

        if (IsKeyPressed(KEY_SPACE)){
            i = (i + 1) % 3;
        }
        BeginDrawing();
        DrawRectangleRec(r1, Color{255,0,0,100});
        DrawRectangleRec(scaleDynamic((Rectangle){0,0,SIZE_X,SIZE_Y}), Color{0,255,0,50});
        DrawRectangleRec(scaleDynamic(r1), Color{0,0,255,100});

        ClearBackground(RAYWHITE);

        if(i == 1){
            GuiSearchPage(&sp);
        } else if(i == 2){
        }


        EndDrawing();

    }


}


