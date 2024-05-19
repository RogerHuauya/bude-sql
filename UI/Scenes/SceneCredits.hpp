#pragma once

#include "SceneMainMenu.hpp"

class Credits : public Scene{
public:
    Credits(){
        Rod = new Button("RODRIGO", GetScreenWidth() / 2 - 150, GetScreenHeight() - 575);
        Rog = new Button("ROGER", GetScreenWidth() / 2 - 150, GetScreenHeight() - 475);
        Ang = new Button("ANGELLO", GetScreenWidth() / 2 - 150, GetScreenHeight() - 375);
        Art = new Button("ARTURO", GetScreenWidth() / 2 - 150, GetScreenHeight() - 275);
        Joe = new Button("JOEL", GetScreenWidth() / 2 - 150, GetScreenHeight() - 175);

        ret = new Button("return", GetScreenWidth() - 300, GetScreenHeight() - 100);
    }

    static void nothing(){}

    static void retr();

    void Render() override{
        GUIManager::WriteText("Project's Members", 0, 40, 45, 1);

        DrawRectangle(GetScreenWidth() / 3, 90, GetScreenWidth() / 3, 2, BLACK);

        Rod->Render(nothing);
        Rog->Render(nothing);
        Ang->Render(nothing);
        Art->Render(nothing);
        Joe->Render(nothing);

        ret->Render(retr);
    };
private:
    Button *Rod, *Ang, *Rog, *Joe, *Art, *ret;
};