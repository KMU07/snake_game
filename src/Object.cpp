#include "Object.h"
#include "Renderer.h"

Object::~Object()
{
    renderer.deregistObject(this);
}

Object::Object(std::string tag)
    : renderer(Renderer::getInstance()), tag(tag)
{
    renderer.registObject(this);
}

uint16_t Object::getRenderOrder() const
{
    return this->renderOrder;
}

bool Object::isHidden() const
{
    return this->hidden;
}
