#pragma once

#include "../Scenes.hpp"

#include "proxy.h"
#include "QueryVisual.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"
//extendible

class Visualize : public Scene{
public:
    static Proxy proxy;
    static QueryVisual *Result;

    Visualize(){
        Return = new Button("return", screenWidth - 300, screenHeight - 80);
    }

    static void ButtonRet();

    void Render() override {
        int key = GetKeyPressed();
        char text[256] = "";
        while (key != KEY_ENTER && !GUIManager::ShouldClose) {
            BeginDrawing();
            ClearBackground(DARKGRAY);
            if (WindowShouldClose()) GUIManager::ShouldClose = true;

            if (key == KEY_BACKSPACE){
                int len = strlen(text);
                text[len-1] = '\0';
            }
            else if (key != KEY_CAPS_LOCK){
                int len = strlen(text);
                text[len] = (char) key;
                text[len + 1] = '\0';
            }

            if (Result != nullptr){
                Result->Update();
                Result->Render();
            }

            Return->Render(ButtonRet);

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
    Button *Return;
};