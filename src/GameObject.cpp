#include "GameObject.h"


GameObject::GameObject(std::string objTag)
    : Object(objTag)
{

}

void GameObject::update() const
{

}

void GameObject::setMove(Callback movement)
{
    this->movement = movement;
}

void GameObject::move()
{
    if (this->movement != nullptr)
        this->movement();
}
