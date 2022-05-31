#ifndef __BIRD_H__
#define __BIRD_H__

#include "Defs.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>

class Bird
{
public:
    sf::Sprite sprite;
    sf::Vector2f vel;

public:
    Bird()
    {
    }
    ~Bird() { }

    void setTexture(sf::Texture& texture)
    {
        sprite.setTexture(texture);
    }

    void flap()
    {
        vel = sf::Vector2f(0, -BIRD_FLAP_VEL);
    }

    void fall(float dt)
    {
        // add gravity to velocity
        vel += sf::Vector2f(0, GRAVITY * dt);

        // add vel to pos for movement
        sprite.setPosition(sprite.getPosition() + vel);
    }
};

#endif /* __BIRD_H__ */
