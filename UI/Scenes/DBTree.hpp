#pragma once

#include "../Scenes.hpp"

#include "../Util/SceneManager.hpp"
#include "../Util/GUIManager.hpp"
#include "../Util/Button.hpp"

class DBTree : public Scene{
public:
    DBTree(){
        RETURN = new Button("return", GetScreenWidth() - 300, GetScreenHeight() - 100);
    }

    static void retr();

    void Render() override{
        DrawText("B-Tree Documentation", 20, 20, 30, BLACK);
        DrawText("A B-tree is a self-balancing tree data structure that maintains sorted data and allows searches, sequential access,", 30, 60, 20, BLACK);
        DrawText("insertions, and deletions in logarithmic time. B-trees are generalized binary search trees where a node can have more", 30, 80, 20, BLACK);
        DrawText("than two children.", 30, 100, 20, BLACK);

        DrawText("Insertion:", 20, 140, 25, BLACK);
        DrawText("First: Insert the key into the appropriate leaf node following the rules of a binary search tree.", 30, 165, 20, BLACK);
        DrawText("Second: If the leaf node exceeds the maximum number of keys, split the node and propagate the split upwards.", 30, 185, 20, BLACK);
        DrawText("Third: Continue splitting until no node exceeds the maximum number of keys, adjusting the tree height if necessary.", 30, 205, 20, BLACK);

        DrawText("Remove:", 20, 240, 25, BLACK);
        DrawText("First: Remove the key from the appropriate node, following the rules of a binary search tree.", 30, 265, 20, BLACK);
        DrawText("Second: If the node has fewer keys than the minimum required, rebalance the tree by borrowing a key from a sibling", 30, 285, 20, BLACK);
        DrawText("or merging nodes.", 30, 305, 20, BLACK);
        DrawText("Third: Continue rebalancing until all nodes meet the minimum key requirement, adjusting the tree height if necessary.", 30, 325, 20, BLACK);

        DrawText("Find:", 20, 360, 25, BLACK);
        DrawText("First: Compare the target value with the keys in the current node.", 30, 385, 20, BLACK);
        DrawText("If the target value is found, return the node. If the target value is less, move to the left child;", 30, 405, 20, BLACK);
        DrawText("if it is greater, move to the right child.", 30, 425, 20, BLACK);

        DrawText("Search in range:", 20, 480, 25, BLACK);
        DrawText("First: Verify if the keys in the current node are within the range of the two bounds.", 30, 505, 20, BLACK);
        DrawText("If a key is within the range, add it to the results and continue searching in both children if necessary.", 30, 525, 20, BLACK);
        DrawText("If a key is less than the lower bound, move to the right child; if it is greater than the upper bound, ", 30, 545, 20, BLACK);
        DrawText("move to the left child.", 30, 565, 20, BLACK);


        RETURN->Render(retr);
    };
private:
    Button *RETURN;
};