#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <SFML/Graphics.hpp>

namespace Daft
{

class InputManager
{
public:
    bool isEntityClicked(sf::Sprite entity, sf::Mouse::Button button, sf::RenderWindow& window);
    sf::Vector2i getMousePos(sf::RenderWindow& window);
};

} // namespace Daft

#endif /* __INPUTMANAGER_H__ */
