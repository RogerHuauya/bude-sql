#pragma once

#include "DAvl.hpp"
#include "DBTree.hpp"
#include "DExtendible.hpp"

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

class SceneDocumen : public Scene{
public:
    SceneDocumen(){
        AVL = new Button("AVL", GetScreenWidth() / 2 - 150, GetScreenHeight() - 575);
        BTREE = new Button("BTree", GetScreenWidth() / 2 - 150, GetScreenHeight() - 450);
        ExtendibleHashing = new Button("Extendible Hash", GetScreenWidth() / 2 - 150, GetScreenHeight() - 325);
        Return = new Button("Return", GetScreenWidth() / 2 - 150, GetScreenHeight() - 200);
    }

    static void ButtonRet();

    static void ButtonAvl(){
        DAVL *Walk;
        Walk = new DAVL();
        SceneManager::LoadScene(Walk);
    }

    static void ButtonBTree(){
        DBTree *Walk;
        Walk = new DBTree();
        SceneManager::LoadScene(Walk);
    }

    static void ButtonExt(){
        DExtendible *Walk;
        Walk = new DExtendible();
        SceneManager::LoadScene(Walk);
    }

    void Render() override{
        GUIManager::WriteText("Documentation", 0, 40, 45, 1);

        DrawRectangle(GetScreenWidth() / 3, 90, GetScreenWidth() / 3, 2, BLACK);

        Return->Render(ButtonRet);
        ExtendibleHashing->Render(ButtonExt);
        BTREE->Render(ButtonBTree);
        AVL->Render(ButtonAvl);
    };
private:
    Button *Return, *ExtendibleHashing, *BTREE, *AVL;
};