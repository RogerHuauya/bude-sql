#pragma once

#include <iostream>

class Scene
{
public:
    virtual ~Scene(){};
    virtual void Render(){};
private:
    std::string name;
};