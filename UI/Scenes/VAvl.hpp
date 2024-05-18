#pragma once

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

#include "cstdlib"

#include "../src/proxy/proxy.h"


class VAVL : public Scene
{
public:
    static Proxy AVL;
    static string TEXT;

    VAVL()
    {
        //mainMenuMusic = LoadMusicStream("rescources/sounds/music/Underclocked.mp3");
        //PlayMusicStream(mainMenuMusic);

        insert = new Button("insert", 25, 100);
        find = new Button("find", 25, 200);
        remove = new Button("remove", 25, 300);
        range = new Button("range", 25, 400);
        ret = new Button("return", 25, 500);
    }

    static void ins(){
        VAVL* Walk;
        Walk = new VAVL();
        SceneManager::LoadScene(Walk);
    }

    static void rem(){
        VAVL* Walk;
        Walk = new VAVL();
        SceneManager::LoadScene(Walk);
    }

    static void fi(){
        VAVL* Walk;
        Walk = new VAVL();
        auto resp = AVL.execute_query(TEXT);
        cout << resp << endl;
        SceneManager::LoadScene(Walk);
    }

    static void ran(){
        VAVL* Walk;
        Walk = new VAVL();
        SceneManager::LoadScene(Walk);
    }

    static void retur();

    static void nothing(){}

    void Render() override
    {
        //UpdateMusicStream(mainMenuMusic);

        int key = GetKeyPressed();
        char text[256] = "";
        while (key != KEY_ENTER && !GUIManager::ShouldClose){
            BeginDrawing();
            DrawText("By Rodrigo", 2, GetScreenHeight() - 22, 20, WHITE);
            ClearBackground(DARKGRAY);
            if(WindowShouldClose()) GUIManager::ShouldClose = true;

            int len = strlen(text);
            text[len] = (char)key;
            text[len + 1] = '\0';

            insert->Render(nothing);
            remove->Render(nothing);
            find->Render(nothing);
            range->Render(nothing);
            ret->Render(nothing);

            DrawText("Enter text:", 0, 0, 50, BLACK);
            DrawRectangleLines(300, 2, 200, 40, BLACK);
            DrawText(text, 310, 0, 50, BLACK);
            key = GetKeyPressed();
            EndDrawing();
        }
        TEXT = text; //texto a mandar al parser;
        while (!GUIManager::ShouldClose){
            BeginDrawing();
            DrawText("By Rodrigo", 2, GetScreenHeight() - 22, 20, WHITE);
            ClearBackground(DARKGRAY);
            if(WindowShouldClose()) GUIManager::ShouldClose = true;

            insert->Render(ins);
            remove->Render(rem);
            find->Render(fi);
            range->Render(ran);
            ret->Render(retur);
            if (insert->IsPressed() || remove->IsPressed() || find->IsPressed() || range->IsPressed() ||
                ret->IsPressed()){
                break;
            }
            text[0] = '\0';
            DrawText("Enter text:", 0, 0, 50, BLACK);
            DrawRectangleLines(300, 2, 200, 40, BLACK);
            DrawText(text, 310, 0, 50, BLACK);
            EndDrawing();
        }
    };
private:
    //Music mainMenuMusic;
    Button *insert, *remove, *find, *range, *ret;
    //Estructura*
};