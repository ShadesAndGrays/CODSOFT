#pragma once
#include <raylib.h>
#include <iostream>


Rectangle scaleDynamic(Rectangle rect){
    float factor = 
        (float)GetScreenWidth()/SIZE_X <= (float)GetScreenHeight()/SIZE_Y ? 
        (float)GetScreenWidth()/SIZE_X :
        (float)GetScreenHeight()/SIZE_Y;

    rect.width = rect.width * factor;
    rect.height = rect.height * factor;
    rect.x =  GetScreenWidth()/2.0 - SIZE_X/2.0 * factor + rect.x * factor;
    rect.y =  GetScreenHeight()/2.0 - SIZE_Y/2.0 * factor + rect.y * factor;

    return rect;
}
