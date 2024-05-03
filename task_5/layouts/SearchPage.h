/*******************************************************************************************
*
*   SearchPage v1.0.0 - SearchPage
*
*   MODULE USAGE:
*       #define GUI_SEARCHPAGE_IMPLEMENTATION
*       #include "gui_SearchPage.h"
*
*       INIT: GuiSearchPageState state = InitGuiSearchPage();
*       DRAW: GuiSearchPage(&state);
*

**********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <vector>

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()
#include <util.h>
#include <BookElement.h>

#ifndef GUI_SEARCHPAGE_H
#define GUI_SEARCHPAGE_H

typedef struct {
    bool Exit;
    bool Button002Pressed;
    bool TextBox003EditMode;
    char SearchText[128];
    bool SearchButtonPressed;
    Rectangle ScrollPanel005ScrollView;
    Vector2 ScrollPanel005ScrollOffset;
    Vector2 ScrollPanel005BoundsOffset;
    std::vector<GuiBookElementState> elements;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiSearchPageState;


#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiSearchPageState InitGuiSearchPage(void);
void GuiSearchPage(GuiSearchPageState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_SEARCHPAGE_H

/***********************************************************************************
*
*   GUI_SEARCHPAGE IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_SEARCHPAGE_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiSearchPageState InitGuiSearchPage(void)
{
    GuiSearchPageState state = { 0 };

    state.Exit = false;
    state.Button002Pressed = false;
    state.TextBox003EditMode = false;
    strcpy(state.SearchText, "");
    state.SearchButtonPressed = false;
    state.ScrollPanel005ScrollView = (Rectangle){ 0, 0, 0, 0 };
    state.ScrollPanel005ScrollOffset = (Vector2){ 0, 0 };
    state.ScrollPanel005BoundsOffset = (Vector2){ 0, 0 };

    for (auto i =0 ; i< 20 ; i ++)
        state.elements.push_back({0});
    // Custom variables initialization


    return state;
}

void GuiSearchPage(GuiSearchPageState *state)
{
    for (auto i = 0; i < state->elements.size(); i++){
        state->elements[i].anchor = Vector2Add(state->ScrollPanel005ScrollOffset, {72.0f + 536.0/2.0 - 368.0f/2 , 140.0f+ (64 +20 )* i}); 

    }
    GuiPanel(scaleDynamic((Rectangle){ 0, 0, 696, 472 }), NULL);
    state->Exit = GuiButton(scaleDynamic((Rectangle){ 24, 24, 32, 24 }), "X" );
    state->Button002Pressed = GuiButton(scaleDynamic((Rectangle){ 600, 24, 72, 24 }), "CheckOut"); 
    if (GuiTextBox(scaleDynamic((Rectangle){ 72, 72, 456, 24 }), state->SearchText, 128, state->TextBox003EditMode)) state->TextBox003EditMode = !state->TextBox003EditMode;
    state->SearchButtonPressed = GuiButton(scaleDynamic((Rectangle){ 544, 72, 56, 24 }), "Search"); 

    Rectangle scrollView = scaleDynamic(state->ScrollPanel005ScrollView);

    GuiScrollPanel(scaleDynamic((Rectangle){ 72, 120, 536 - state->ScrollPanel005BoundsOffset.x, 320 - state->ScrollPanel005BoundsOffset.y }), NULL, scaleDynamic((Rectangle){ 72, 120, 536 , 320+ (74.0f * state->elements.size()) }), &state->ScrollPanel005ScrollOffset,&scrollView );
    GuiLabel(scaleDynamic((Rectangle){ 104, 24, 456, 32 }), "SAMPLE TEXT");

    BeginScissorMode(scrollView.x, scrollView.y,scrollView.width , scrollView.height);
    // DrawRectangle(scrollView.x + 20, 30, 1000,1000, Color{0,0,100,255});

    for (auto i = 0; i < state->elements.size(); i++){
        GuiBookElement(&state->elements[i]);

    }
    EndScissorMode();
}

#endif // GUI_SEARCHPAGE_IMPLEMENTATION
