#pragma once

#include <iostream>
#include "raylib.h"

using namespace std;

class GUIManager
{
public:
    /// @brief Write text to screen
    /// @param text text to print out
    /// @param x position, if centered, put it at anything
    /// @param y y position
    /// @param font size of the font
    /// @param center boolean
    static void WriteText(string text, int x, int y, int font, int center)
    {
        if(center)
        {
            DrawText(text.c_str() , (GetScreenWidth() / 2) - (MeasureText(text.c_str(), font) / 2), y, font, BLACK);
        }else{
            DrawText(text.c_str(), x, y, font, BLACK);
        }
    };
    inline static bool ShouldClose = false;
};