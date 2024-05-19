#include "SceneMainMenu.hpp"

void Visualize::ButtonRet(){
    SceneMainMenu *Walk;
    Walk = new SceneMainMenu();
    SceneManager::LoadScene(Walk);
}

Proxy Visualize::proxy;
QueryVisual* Visualize::Result = nullptr;

void Credits::retr() {
    SceneMainMenu *Walk;
    Walk = new SceneMainMenu();
    SceneManager::LoadScene(Walk);
}

