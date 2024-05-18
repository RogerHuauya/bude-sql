#pragma once

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

class DBTree : public Scene
{
public:
    DBTree()
    {
        //mainMenuMusic = LoadMusicStream("rescources/sounds/music/Underclocked.mp3");
        //PlayMusicStream(mainMenuMusic);
        RETURN = new Button("return", GetScreenWidth() - 300, GetScreenHeight() - 100);

    }

    static void retr();

    void Render() override
    {
        DrawText("BTree+ Documentation", 20, 20, 30, BLACK);
        DrawText("An AVL tree is a self-balancing binary search tree where the difference between the heights of the left and right ", 30, 60, 20, BLACK);
        DrawText("subtrees of any node is at most one.", 30, 80, 20, BLACK);

        DrawText("Insertion:", 20, 120, 25, BLACK);


        DrawText("Remove:", 20, 220, 25, BLACK);


        DrawText("Find:", 20, 320, 25, BLACK);


        DrawText("Search in range:", 20, 420, 25, BLACK);

        RETURN->Render(retr);
    };
private:
    //Music mainMenuMusic;
    Button *RETURN;
    //Estructura*
};