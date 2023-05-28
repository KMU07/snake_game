#pragma once
#include <functional>
#include <string>
#include "Object.h"

#define Callback std::function<void()>


class GameObject : public Object
{
private:
    Callback movement;
    virtual void update() const final;

public:
    GameObject(std::string objTag);
    virtual void setMove(Callback movement) final;
    virtual void move() final;
};
