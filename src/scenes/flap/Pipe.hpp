#ifndef __PIPE_H__
#define __PIPE_H__

#include "Defs.hpp"
#include <SFML/Graphics.hpp>

namespace Daft
{

class Pipe
{
public:
    sf::Sprite upper;
    sf::Sprite lower;
    sf::Vector2f pos;
    sf::Vector2f vel = { -1.5f, 0 };

    bool bSpawnNewPipe = true;
    bool bScored = false;

public:
    Pipe()
    {
        int startWindow = SCREEN_HEIGHT / 2;
        float startPos = (std::rand() % startWindow) + SCREEN_HEIGHT / 3;

        upper.setScale(2.f, -2.f);
        lower.setScale(2.f, 2.f);

        setPosition(sf::Vector2f(SCREEN_WIDTH + 64, startPos));
    }
    ~Pipe()
    {
    }

    void setPosition(sf::Vector2f newPos)
    {
        pos = newPos;
        upper.setPosition(newPos.x, (newPos.y - 64) - 24);
        lower.setPosition(newPos.x, newPos.y + 24);
    }

    void move(float dt)
    {
        setPosition(pos + vel);
    }
};

}

#endif /* __PIPE_H__ */
