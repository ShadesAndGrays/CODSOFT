/*******************************************************************************************
*
*   BookElement v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_BOOKELEMENT_IMPLEMENTATION
*       #include "gui_BookElement.h"
*
*       INIT: GuiBookElementState state = InitGuiBookElement();
*       DRAW: GuiBookElement(&state);
*
**********************************************************************************************/

#include "raylib.h"
#include "util.h"
#include <string>

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_BOOKELEMENT_H
#define GUI_BOOKELEMENT_H

typedef struct {
    bool isBorrowed;
    bool unborrowPressed;
    
    
    char title[128];
    char author[128];
    char isbn[15];
    int copies;

    Vector2 anchor;
    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiBookElementState;

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
GuiBookElementState InitGuiBookElement(void);
void GuiBookElement(GuiBookElementState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_BOOKELEMENT_H

/***********************************************************************************
*
*   GUI_BOOKELEMENT IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_BOOKELEMENT_IMPLEMENTATION)

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
GuiBookElementState InitGuiBookElement(void)
{
    GuiBookElementState state = { 0 };

    state.isBorrowed = false;
    state.unborrowPressed = false;


    strcpy(state.author, "");
    strcpy(state.title, "");
    strcpy(state.isbn, "");
    state.copies = 0;
    

        state.anchor = {0};
    // Custom variables initialization

    return state;
}

void GuiBookElement(GuiBookElementState *state)
{
    GuiPanel(scaleDynamic((Rectangle){ state->anchor.x + 8,state->anchor.y + -8, 368, 64 }), NULL);

    GuiLabel(scaleDynamic((Rectangle){ state->anchor.x + 18,state->anchor.y + -8, 320, 40 }), state->title);
    GuiCheckBox(scaleDynamic((Rectangle){ state->anchor.x + 306, state->anchor.y + 8, 16, 16 }), !state->isBorrowed ? "Borrow" : "",&state->isBorrowed );
    if (state->isBorrowed)
        state->unborrowPressed = GuiButton(scaleDynamic((Rectangle){ state->anchor.x + 336, state->anchor.y + 8, 16, 16 }), "X" );
    GuiLabel(scaleDynamic((Rectangle){ state->anchor.x + 18, state->anchor.y + 32, 96, 24 }), state->author);
    char isbn[30] = "ISBN: ";
    strcat(isbn, state->isbn);
    GuiLabel(scaleDynamic((Rectangle){ state->anchor.x + 18, state->anchor.y + 16, 96, 24 }),isbn );

    GuiLabel(scaleDynamic((Rectangle){ state->anchor.x + 208, state->anchor.y + 32, 120, 24 }), std::to_string(state->copies).c_str());
}

#endif // GUI_BOOKELEMENT_IMPLEMENTATION
