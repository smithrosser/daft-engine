#include "Game.hpp"
#include "FlapScene.hpp"

namespace Daft
{

/**
    @brief Creates a new Game object with parameters supplied.

    @param width Window width
    @param height Window height
    @param title Window titles
 */
Game::Game(int width, int height, const std::string& title)
{
    _context->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
    _context->sceneMgr.push(SceneRef(new FlapScene(_context)));
}

/**
    @brief Starts the game loop.

    @return int Non-zero for error
 */
int Game::run()
{
    float newTime, frameTime, currentTime, accumulator, interpolation;

    currentTime = _clock.getElapsedTime().asSeconds();
    accumulator = 0.0f;

    while (_context->window.isOpen())
    {
        _context->sceneMgr.update();

        // ensure motion is consistent over varying FPS
        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        frameTime = (frameTime > 0.25f) ? 0.25f : frameTime;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= _dt)
        {
            _context->sceneMgr.peek()->poll();
            _context->sceneMgr.peek()->update(_dt);

            accumulator -= _dt;
        }

        interpolation = accumulator / _dt;
        _context->sceneMgr.peek()->render(interpolation);
    }

    return EXIT_SUCCESS;
}

} // namespace Daft
