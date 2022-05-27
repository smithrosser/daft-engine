#include "BasicScene.hpp"

namespace Daft
{

BasicScene::BasicScene(ContextRef context)
    : _context(context)
{
}

BasicScene::~BasicScene()
{
}

void BasicScene::init()
{
}

void BasicScene::poll()
{
    sf::Event event;

    while (_context->window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            _context->window.close();
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void BasicScene::update(float dt)
{
}

void BasicScene::render(float dt)
{
    _context->window.clear();
    _context->window.display();
}

}
