#pragma once

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

#include "../Util/QueryVisual.hpp"
#include "../src/proxy/proxy.h"

class VBTree : public Scene
{
public:

    static Proxy proxy;
    static QueryVisual *Result;

    VBTree()
    {
        //mainMenuMusic = LoadMusicStream("rescources/sounds/music/Underclocked.mp3");
        //PlayMusicStream(mainMenuMusic);
        Return = new Button("return", screenWidth - 300, screenHeight - 80);
    }

    static void retur();

    void Render() override {
        //UpdateMusicStream(mainMenuMusic);

        int key = GetKeyPressed();
        char text[256] = "";
        while (key != KEY_ENTER && !GUIManager::ShouldClose) {
            BeginDrawing();
            DrawText("By Rodrigo", 2, GetScreenHeight() - 22, 20, WHITE);
            ClearBackground(DARKGRAY);
            if (WindowShouldClose()) GUIManager::ShouldClose = true;

            if (key == KEY_BACKSPACE){
                int len = strlen(text);
                text[len-1] = '\0';
            }
            else if (key != KEY_CAPS_LOCK && key != KEY_LEFT_ALT && key != KEY_TAB){
                int len = strlen(text);
                text[len] = (char) key;
                text[len + 1] = '\0';
            }

            if (Result != nullptr){
                Result->Update();
                Result->Render();
            }

            Return->Render(retur);

            DrawText("Query:", 10, 10, 20, WHITE);
            DrawText(text, 80, 10, 20, WHITE);
            key = GetKeyPressed();
            EndDrawing();
        }
        string x = text; //texto a mandar al parser;
        QueryResult query_result = proxy.execute_query(x);
        // "CREATE TABLE users FROM FILE 'D:/Documentos/Rodrigo/Utec/ciclo 2024-1/BD II/Unir/cmake-build-debug/AppleStore.csv' USING INDEX HASH ('id');"
        //"SELECT track_name FROM users WHERE id=284882215;"
        Result = new QueryVisual(query_result);
    }
private:
    //Music mainMenuMusic;
    //Estructura*
    Button *Return;
};