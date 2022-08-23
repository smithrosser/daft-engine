#include "InputManager.hpp"

namespace Daft
{

/**
    @brief Checks whether a given entity has been clicked.

    @param entity The entity to check
    @param button Which mouse button was pressed
    @param window The current window
    @return true Clicked
    @return false Not clicked
 */
bool InputManager::isEntityClicked(sf::Sprite entity, sf::Mouse::Button button, sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        sf::IntRect tempRect(sf::Vector2i(entity.getPosition().x, entity.getPosition().y), sf::Vector2i(entity.getGlobalBounds().width, entity.getGlobalBounds().height));

        return tempRect.contains(sf::Mouse::getPosition(window));
    }

    return false;
}

/**
    @brief Retrieves the current mouse position.

    @param window The current window
    @return sf::Vector2i Current mouse position
 */
sf::Vector2i InputManager::getMousePos(sf::RenderWindow& window)
{
    return sf::Mouse::getPosition(window);
}

}
