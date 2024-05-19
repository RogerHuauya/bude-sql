#pragma once

#include <cstring>
#include <string>
#include <iostream>

#include "raylib.h"

class Button
{
public:
    Button(std::string name, int posX, int posY)
    {
        this->X = posX;
        this->Y = posY;

        const int length = name.length();
        char* char_array = new char[length + 1];

        std::strcpy(char_array, name.c_str());

        this->name = char_array;
    };


    /// @brief Render button on screen, if it's hovered, it will be in another color
    /// @param _setup function that will be executed when the button is clicked
    void Render(void (*_setup)())
    {

        DrawRectangle(X + 25, Y, 250, 75, (isHovered(GetMouseX(), GetMouseY()) ? RED : BLACK));

        DrawRectangle(X + 30, Y + 5, 240, 65, (isHovered(GetMouseX(), GetMouseY()) ? BLACK : WHITE));

        DrawText(name, X + (150 - MeasureText(name, 30) / 2), Y + 25, 30, (isHovered(GetMouseX(), GetMouseY()) ? RED : BLACK));

        hovered = isHovered(GetMouseX(), GetMouseY());

        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            _setup(); // Ejecuta la función asociada al botón
            pressed = true; // Marca el botón como presionado
        }
    }

    void ResetPressedState()
    {
        pressed = false;
    }

    // Método para verificar si el botón ha sido presionado
    bool IsPressed() const
    {
        return pressed;
    }
private:
    bool hovered;
    int X, Y;
    char* name;
    void onclick(void (*onclick)()) {onclick();};
    bool pressed = false;

    /// @brief Function to find
    /// @param posX position X of the cursor
    /// @param posY position Y of the cursor
    /// @return true if hovered, false otherwise
    int isHovered(int posX, int posY)
    {
        return (posX < X + 250 && posX > X && posY < Y + 75 && posY > Y);
    };
};