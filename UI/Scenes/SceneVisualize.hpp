#pragma once

#include "VAvl.hpp"
#include "VBTree.hpp"
#include "VExtendible.hpp"

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

#include "../src/bplus/bplus.h"
//extendible

class Visualize : public Scene
{
public:
    Visualize()
    {
        //mainMenuMusic = LoadMusicStream("rescources/sounds/music/NightShade.mp3");
        //PlayMusicStream(mainMenuMusic);

        AVL = new Button("AVL", GetScreenWidth() / 2 - 150, GetScreenHeight() - 575);
        BTREE = new Button("BTree", GetScreenWidth() / 2 - 150, GetScreenHeight() - 450);
        ExtendibleHashing = new Button("Extendible Hash", GetScreenWidth() / 2 - 150, GetScreenHeight() - 325);
        Return = new Button("Return", GetScreenWidth() / 2 - 150, GetScreenHeight() - 200);
    }

    static void ButtonRet();

    static void ButtonAvl()
    {
        VAVL *Walk;
        Walk = new VAVL();
        SceneManager::LoadScene(Walk);
    }

    static void ButtonBTree()
    {
        VBTree *Walk;
        Walk = new VBTree();
        SceneManager::LoadScene(Walk);
    }

    static void ButtonExt()
    {
        VExtendible *Walk;
        Walk = new VExtendible();
        SceneManager::LoadScene(Walk);
    }

    void Render() override{
        //UpdateMusicStream(mainMenuMusic);
        GUIManager::WriteText("Visualization", 0, 40, 45, 1);

        DrawText("By Rodrigo", 2, GetScreenHeight() - 22, 20, WHITE);

        DrawRectangle(GetScreenWidth() / 3, 90, GetScreenWidth() / 3, 2, BLACK);

        Return->Render(ButtonRet);
        ExtendibleHashing->Render(ButtonExt);
        BTREE->Render(ButtonBTree);
        AVL->Render(ButtonAvl);
    };
private:
    //Music mainMenuMusic;
    Button *Return, *ExtendibleHashing, *BTREE, *AVL;
};