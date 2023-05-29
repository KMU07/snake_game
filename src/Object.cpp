#include "Object.h"


// todo: Object::renderer initializer 구현 필요함
Object::Object(std::string tag)
    : tag(tag), renderer()
{
    // renderer.registObject(this);
}

Object::~Object()
{
    // renderer.deregistObject(this);
}

uint16_t Object::getRenderOrder() const
{
    return this->renderOrder;
}

bool Object::isHidden() const
{
    return this->hidden;
}
