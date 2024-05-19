#pragma once

#include <iostream>
#include "raylib.h"

#include "SceneVisualize.hpp"
#include "SceneDocumen.hpp"
#include "SceneCredits.hpp"

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

class SceneMainMenu : public Scene{
public:
    SceneMainMenu(){
        Queries = new Button("Queries", GetScreenWidth() / 2 - 150, GetScreenHeight() - 575);
        Documentation = new Button("Documentation", GetScreenWidth() / 2 - 150, GetScreenHeight() - 450);
        Credit = new Button("Credits", GetScreenWidth() / 2 - 150, GetScreenHeight() - 325);
        Quit = new Button("Quit", GetScreenWidth() / 2 - 150, GetScreenHeight() - 200);
    }

    static void ButtonQuit(){
        GUIManager::ShouldClose = true;
    }

    static void ButtonCredits()    {
        Credits *Walk;
        Walk = new Credits();
        SceneManager::LoadScene(Walk);
    }

    static void ButtonVisual()    {
        Visualize *Walk;
        Walk = new Visualize();
        SceneManager::LoadScene(Walk);
    }

    static void ButtonDoc()    {
        SceneDocumen *Walk;
        Walk = new SceneDocumen();
        SceneManager::LoadScene(Walk);
    }

    void Render() override{
        GUIManager::WriteText("BD2 Project", 0, 40, 45, 1);

        DrawRectangle(GetScreenWidth() / 3, 90, GetScreenWidth() / 3, 2, BLACK);

        Quit->Render(ButtonQuit);
        Credit->Render(ButtonCredits);
        Documentation->Render(ButtonDoc);
        Queries->Render(ButtonVisual);
    };
private:
    Button *Quit, *Queries, *Documentation, *Credit;
};