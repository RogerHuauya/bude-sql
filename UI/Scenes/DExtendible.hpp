#pragma once

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

class DExtendible : public Scene{
public:
    DExtendible(){
        RETURN = new Button("return", GetScreenWidth() - 300, GetScreenHeight() - 100);
    }

    static void retr();

    void Render() override{
        DrawText("Extendible Hashing Documentation", 20, 20, 30, BLACK);
        DrawText("Extendible hashing is a dynamic hashing technique that adjusts the hash table size to accommodate the number ", 30, 60, 20, BLACK);
        DrawText("of entries.", 30, 80, 20, BLACK);
        DrawText("It uses a directory of pointers to buckets, which can split as the number of entries increases, allowing efficient ", 30, 100, 20, BLACK);
        DrawText("data retrieval.", 30, 120, 20, BLACK);

        DrawText("Insertion:", 20, 140, 25, BLACK);
        DrawText("First: Compute the hash of the key and use it to index into the directory.", 30, 165, 20, BLACK);
        DrawText("Second: If the corresponding bucket has space, insert the key into the bucket.", 30, 185, 20, BLACK);
        DrawText("Third: If the bucket is full, split the bucket and redistribute the entries. Increase the global depth if necessary.", 30, 205, 20, BLACK);
        DrawText("Fourth: Update the directory to reflect the new buckets.", 30, 225, 20, BLACK);

        DrawText("Remove:", 20, 260, 25, BLACK);
        DrawText("First: Compute the hash of the key and use it to index into the directory.", 30, 285, 20, BLACK);
        DrawText("Second: Locate the bucket containing the key.", 30, 305, 20, BLACK);
        DrawText("Third: Remove the key from the bucket.", 30, 325, 20, BLACK);
        DrawText("Fourth: If removing the key causes the bucket to be underfull, merge buckets if possible and update the directory.", 30, 345, 20, BLACK);

        DrawText("Find:", 20, 380, 25, BLACK);
        DrawText("First: Compute the hash of the key and use it to index into the directory.", 30, 405, 20, BLACK);
        DrawText("Second: Locate the bucket corresponding to the hash value.", 30, 425, 20, BLACK);
        DrawText("Third: Search within the bucket for the target key.", 30, 445, 20, BLACK);

        RETURN->Render(retr);
    };
private:
    Button *RETURN;
};