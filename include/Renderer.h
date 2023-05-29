#pragma once
#include <list>

class Object;

// This class is singleton pattern.
class Renderer
{
    std::list<Object*> objects;

    Renderer() = default;
public:
    static Renderer& getInstance();

    void registObject(Object* obj);
    void deregistObject(Object* obj);

    // Render all registed objects.
    // Assert: If object deque is not sorted, something bad happened at registObject or somewhere.
    void renderWorld();

    // You can't use copy constructor on singleton class!
    Renderer(const Renderer&) = delete;
    // You can't use copy operator on singleton class!
    Renderer& operator=(const Renderer&) = delete;
};
