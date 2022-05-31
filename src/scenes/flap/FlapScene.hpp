#ifndef __FLAPSCENE_H__
#define __FLAPSCENE_H__

#include "Bird.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <list>

namespace Daft
{

class FlapScene : public Scene
{
private:
    ContextRef _context;

    Bird _bird;
    std::list<Pipe> _pipes;
    std::array<sf::Sprite, 3> _clouds;
    sf::Text _gameOverText;
    sf::Text _scoreText;
    uint32_t _score = 0;
    bool _isGameOver = false;
    sf::Clock _clock;
    int _gameOverTime;

public:
    FlapScene(ContextRef context)
        : _context(context)
    {
    }
    ~FlapScene() { }

    void init();
    void poll();
    void update(float dt);
    void render(float dt);

    void createPipe();
    void createCloud();
    void incrementScore();
    void gameOver();
};

}

#endif /* __FLAPSCENE_H__ */
