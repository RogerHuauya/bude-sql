#include "SceneMainMenu.hpp"

void Visualize::ButtonRet(){
    SceneMainMenu *Walk;
    Walk = new SceneMainMenu();
    SceneManager::LoadScene(Walk);
}

void Credits::retr() {
    SceneMainMenu *Walk;
    Walk = new SceneMainMenu();
    SceneManager::LoadScene(Walk);
}

void VAVL::retur() {
    Visualize *Walk;
    Walk = new Visualize();
    SceneManager::LoadScene(Walk);
}

void VBTree::retur() {
    Visualize *Walk;
    Walk = new Visualize();
    SceneManager::LoadScene(Walk);
}

void VExtendible::retur() {
    Visualize *Walk;
    Walk = new Visualize();
    SceneManager::LoadScene(Walk);
}
