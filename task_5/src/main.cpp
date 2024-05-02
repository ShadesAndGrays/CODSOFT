#include <database.hpp>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION 
#include <raygui.h>
#include <SearchPage.h>
#include <util.h>




int main() {
    // auto db = DatabaseManger::getInstance();

    InitWindow(SIZE_X,SIZE_Y,"BookKeeper");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    GuiSearchPageState sp = InitGuiSearchPage(); 

    Rectangle r1 {5,5,100,100};


    int i = 0;
    while(!WindowShouldClose()){
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


