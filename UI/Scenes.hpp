#pragma once

#include <iostream>

const int screenWidth = 1280;
const int screenHeight = 720;

class Scene
{
public:
    virtual ~Scene(){};
    virtual void Render(){};
private:
    std::string name;
};