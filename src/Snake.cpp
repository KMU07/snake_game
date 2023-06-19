#include <chrono>
#include <exception>
#include <cassert>
#include "Snake.h"
#include "Wall.h"
#include "Booster.h"
#include "Gate.h"

const Color Snake::headColor = Color::Blue;
const Color Snake::bodyColor = Color::Yellow;

Snake::Snake(SnakeStatus& status, Vector2Int head, Vector2Int body, Vector2Int tail)
    : GameObject("Snake", 0), status(status)
{
    pixels.clear();

    Pixel pixel;

    pixel.chColor = headColor;
    pixel.pos = head;
    pixels.push_back(pixel);

    pixel.chColor = bodyColor;
    pixel.pos = body;
    pixels.push_back(pixel);

    pixel.chColor = bodyColor;
    pixel.pos = tail;
    pixels.push_back(pixel);

    headDirection = head - body;
    tailDirection = tail - body;
}

void Snake::addHead()
{
    Pixel head = pixels.front();

    head.pos += headDirection;
    pixels[0].chColor = bodyColor;

    pixels.push_front(head);
    status.currentLength++;
}

void Snake::popHead()
{
    headDirection = pixels[0].pos - pixels[1].pos;
    pixels.pop_front();
    pixels[0].chColor = headColor;
    status.currentLength--;
}

void Snake::addTail()
{
    Pixel pixel = pixels.back();

    pixel.pos += tailDirection;
    pixel.chColor = bodyColor;

    pixels.push_back(pixel);
    status.currentLength++;
}

void Snake::popTail()
{
    tailDirection = pixels.back().pos - (pixels.end() - 2)->pos;
    pixels.pop_back();
    status.currentLength--;
}

bool Snake::isPassingGate() const
{
    return passingGate;
}

bool Snake::isDead() const
{
    return dead;
}

size_t Snake::getBodyLength() const
{
    return pixels.size();
}

std::string Snake::getReasonOfDeath() const
{
    return reasonOfDeath;
}

void Snake::update()
{
    static auto prevInput = std::chrono::system_clock::now();
    static auto prevMove = std::chrono::system_clock::now();

    const auto now = std::chrono::system_clock::now();

    // Get user input and process
    if (prevInput + INPUT_INTERVAL <= now)
    {
        chtype key = getch();

        if (key != ERR)
        {
            switch (key)
            {
            case KEY_UP:
                headDirection = Vector2Int::up;
                break;
            case KEY_DOWN:
                headDirection = Vector2Int::down;
                break;
            case KEY_LEFT:
                headDirection = Vector2Int::left;
                break;
            case KEY_RIGHT:
                headDirection = Vector2Int::right;
                break;
            }

            assert(pixels.size() >= 3);

            // User pressed in the direction of the body at the back of the head
            if (pixels[0].pos + headDirection == pixels[1].pos)
            {
                reasonOfDeath = "You pressed in the direction of the body at the back of the head.";
                dead = true;
                return;
            }
        }

        prevInput += INPUT_INTERVAL;
    }

    // Move snake
    if (prevMove + SNAKE_MOVE_INTERVAL - boosted <= now)
    {
        this->addHead();
        this->popTail();

        if (passingGate)
        {
            lenBodyNotGateThrough--;

            if (lenBodyNotGateThrough == 0)
                passingGate = false;
        }

        prevMove += SNAKE_MOVE_INTERVAL;
    }
}

void Snake::onCollision(GameObject* other)
{
    assert(other != nullptr);

    if (other == this)
    {
        reasonOfDeath = "You crashed with your body.";
        dead = true;
    }
    else if (other->tag == "Wall")
    {
        Wall* wall = dynamic_cast<Wall*>(other);

        assert(wall != nullptr);

        if (wall->bounce)
        {
            this->popHead();
            std::reverse(pixels.begin(), pixels.end());

            pixels.front().chColor = headColor;
            pixels.back().chColor = bodyColor;

            tailDirection = headDirection;
            headDirection = -headDirection;

            if (pixels.size() < 3)
            {
                reasonOfDeath = "The length of body became smaller than 3.";
                dead = true;
            }

            status.wallBounced++;
        }
        else if (wall->isGate())
        {
            Gate* gate = dynamic_cast<Gate*>(wall);

            assert(gate != nullptr);

            const auto exit = gate->getExit(headDirection);

            pixels[0].pos = exit.first;
            headDirection = exit.second;

            status.gatePass++;
        }
        else
        {
            reasonOfDeath = "You crashed into the wall.";
            dead = true;
        }
    }
    else if (other->tag == "Booster")
    {
        Booster* booster = dynamic_cast<Booster*>(other);

        if (SNAKE_MOVE_INTERVAL + boosted + booster->boosting < 5ms)
            boosted += booster->boosting;

        status.boosterGets++;
    }
    else if (other->tag == "Apple")
    {
        this->addTail();
        status.appleGets++;
    }
    else if (other->tag == "Poison")
    {
        this->popTail();
        status.poisonGets++;

        if (pixels.size() < 3)
        {
            reasonOfDeath = "The length of body became smaller than 3.";
            dead = true;
        }
    }
    else
    {
        // Unexpected GameObject error
        const std::string errorMsg = std::format(
            "Unexpected call occurred at Snake::onCollision\notherTag: {}",
            other->tag
        );

        throw std::exception(errorMsg.c_str());
    }
}
