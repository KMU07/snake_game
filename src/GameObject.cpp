#include "GameEngine.h"
#include "GameObject.h"

GameObject::~GameObject()
{
    engine.deregistObject(this);
}

GameObject::GameObject(const std::string& tag, const uint16_t procOrder)
    : engine(GameEngine::getInstance()), tag(tag), processOrder(procOrder)
{
    engine.registObject(this);
}

bool GameObject::isCollisionable() const
{
    return true;
}

void GameObject::update()
{}

void GameObject::onCollision(GameObject* const other)
{}
