#pragma once

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

class DAVL : public Scene
{
public:
    DAVL()
    {
        //mainMenuMusic = LoadMusicStream("rescources/sounds/music/Underclocked.mp3");
        //PlayMusicStream(mainMenuMusic);

        RETURN = new Button("return", GetScreenWidth() - 300, GetScreenHeight() - 100);

    }

    static void retr();

    void Render() override
    {
        DrawText("AVL Tree Documentation", 20, 20, 30, BLACK);
        DrawText("An AVL tree is a self-balancing binary search tree where the difference between the heights of the left and right ", 30, 60, 20, BLACK);
        DrawText("subtrees of any node is at most one.", 30, 80, 20, BLACK);

        DrawText("Insertion:", 20, 120, 25, BLACK);
        DrawText("First: Insert node as in a binary search tree.", 30, 145, 20, BLACK);
        DrawText("Second: Update the heights of affected nodes.", 30, 165, 20, BLACK);
        DrawText("Third: Check the balance factors from the newly inserted node up to the root.", 30, 185, 20, BLACK);
        DrawText("Fourth: Perform the necessary rotations to restore balance if any node becomes unbalanced.", 30, 205, 20, BLACK);

        DrawText("Remove:", 20, 240, 25, BLACK);
        DrawText("First: Get the predecessor and change the value of the current node then remove the new value in the left subtree.", 30, 265, 20, BLACK);
        DrawText("Second: Update the heights of affected nodes.", 30, 285, 20, BLACK);
        DrawText("Third: Update the heights of affected nodes.", 30, 305, 20, BLACK);
        DrawText("Fourth: Check the balance factors of affected nodes. Perform the necessary rotations to restore balance.", 30, 325, 20, BLACK);

        DrawText("Find:", 20, 360, 25, BLACK);
        DrawText("First: Compare the target value with the value of the current node.", 30, 385, 20, BLACK);
        DrawText("If the target value is equal to the value of the current node, add the current node to results and move to ", 30, 405, 20, BLACK);
        DrawText("both children, if it is less move to the left child and if it is greater move to the right child.", 30, 425, 20, BLACK);

        DrawText("Search in range:", 20, 480, 25, BLACK);
        DrawText("First: Verify if the current node is within the range of the two bounds.", 30, 505, 20, BLACK);
        DrawText("If the current node value is in the range add the current node to results and move to both childs,", 30, 525, 20, BLACK);
        DrawText("if it is less move to the left child and if it is greater move to the right child.", 30, 545, 20, BLACK);

        RETURN->Render(retr);
    };
private:
    //Music mainMenuMusic;
    Button *RETURN;
    //Estructura*
};