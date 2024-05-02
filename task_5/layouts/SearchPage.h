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

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()
#include <util.h>

#ifndef GUI_SEARCHPAGE_H
#define GUI_SEARCHPAGE_H

typedef struct {
    bool Toggle001Active;
    bool Button002Pressed;
    bool TextBox003EditMode;
    char TextBox003Text[128];
    bool Button004Pressed;
    Rectangle ScrollPanel005ScrollView;
    Vector2 ScrollPanel005ScrollOffset;
    Vector2 ScrollPanel005BoundsOffset;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiSearchPageState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

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

    state.Toggle001Active = true;
    state.Button002Pressed = false;
    state.TextBox003EditMode = false;
    strcpy(state.TextBox003Text, "");
    state.Button004Pressed = false;
    state.ScrollPanel005ScrollView = (Rectangle){ 0, 0, 0, 0 };
    state.ScrollPanel005ScrollOffset = (Vector2){ 0, 0 };
    state.ScrollPanel005BoundsOffset = (Vector2){ 0, 0 };

    // Custom variables initialization

    return state;
}

void GuiSearchPage(GuiSearchPageState *state)
{
    GuiPanel(scaleDynamic((Rectangle){ 0, 0, 696, 472 }), NULL);
    GuiToggle(scaleDynamic((Rectangle){ 24, 24, 32, 24 }), "<-", &state->Toggle001Active);
    state->Button002Pressed = GuiButton(scaleDynamic((Rectangle){ 600, 24, 72, 24 }), "CheckOut"); 
    if (GuiTextBox(scaleDynamic((Rectangle){ 72, 72, 456, 24 }), state->TextBox003Text, 128, state->TextBox003EditMode)) state->TextBox003EditMode = !state->TextBox003EditMode;
    state->Button004Pressed = GuiButton(scaleDynamic((Rectangle){ 544, 72, 56, 24 }), "Search"); 
    // GuiScrollPanel((Rectangle){ 72, 120, 536 - state->ScrollPanel005BoundsOffset.x, 320 - state->ScrollPanel005BoundsOffset.y }, NULL, (Rectangle){ 72, 120, 536, 320 }, &state->ScrollPanel005ScrollOffset, &state->ScrollPanel005ScrollView);
    GuiLabel(scaleDynamic((Rectangle){ 104, 24, 456, 32 }), "SAMPLE TEXT");
}

#endif // GUI_SEARCHPAGE_IMPLEMENTATION
