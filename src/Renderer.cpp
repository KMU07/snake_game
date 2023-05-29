#include <cassert>
#include <deque>
#include "Renderer.h"
#include "Object.h"

Renderer& Renderer::getInstance()
{
    static Renderer instance;
    return instance;
}

void Renderer::registObject(Object* const obj)
{
    auto insertIter = objects.end();

    // Find the iterator where this object should be inserted.
    for (auto itr = objects.begin(); itr != objects.end(); ++itr)
    {
        if ((*itr)->getRenderOrder() > obj->getRenderOrder())
        {
            insertIter = itr;
            break;
        }
    }

    objects.insert(insertIter, obj);
}

void Renderer::deregistObject(Object* const obj)
{
    for (auto itr = objects.begin(); itr != objects.end(); ++itr)
    {
        if (*itr == obj)
        {
            objects.erase(itr);
            break;
        }
    }
}

void Renderer::renderWorld()
{
    uint16_t prevRenderOrder = 0;

    // Check sorted and update.
    for (Object* const nowObj : objects)
    {
        assert(prevRenderOrder <= nowObj->getRenderOrder());
        if (!nowObj->isHidden())
            nowObj->update();
    }
}
