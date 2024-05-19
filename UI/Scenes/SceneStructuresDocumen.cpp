#include "SceneMainMenu.hpp"

void SceneDocumen::ButtonRet(){
    SceneMainMenu *Walk;
    Walk = new SceneMainMenu();
    SceneManager::LoadScene(Walk);
}

void DAVL::retr() {
    SceneDocumen *Walk;
    Walk = new SceneDocumen();
    SceneManager::LoadScene(Walk);
}

void DBTree::retr() {
    SceneDocumen *Walk;
    Walk = new SceneDocumen();
    SceneManager::LoadScene(Walk);
}

void DExtendible::retr() {
    SceneDocumen *Walk;
    Walk = new SceneDocumen();
    SceneManager::LoadScene(Walk);
}