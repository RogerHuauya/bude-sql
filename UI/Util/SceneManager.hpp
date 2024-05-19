#pragma once

#include "../Scenes.hpp"

class SceneManager
{
public:
    static void LoadScene(Scene* _scene)
    {
        scene = _scene;
        isSceneLoaded = 1;
    };

    static void Update()
    {
        scene->Render();
    };

    static int SceneLoaded()
    {
        return isSceneLoaded;
    };
private:
    inline static int isSceneLoaded;
    inline static Scene *scene;
};