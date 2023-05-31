#pragma once
#include <deque>
#include <string>
#include "Pixel.h"

class Renderer;

class Object
{
protected:
    Renderer& renderer;

    std::deque<Pixel> pixels;
    uint16_t renderOrder = 0;
    bool hidden = false;

public:
    const std::string tag;

    virtual ~Object();
    Object(std::string tag);

    uint16_t getRenderOrder() const;
    bool isHidden() const;

    // 일정 시간마다 주기적으로 호출되는 함수
    virtual void update() = 0;
};
