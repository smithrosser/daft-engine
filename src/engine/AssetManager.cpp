
#include "AssetManager.hpp"

namespace Daft
{

/**
    @brief Loads in a texture from the filesystem.

    @param id The texture's ID
    @param path Path to the texture file
 */
void AssetManager::loadTexture(const std::string& id, const std::string& path)
{
    sf::Texture texture;

    if (texture.loadFromFile(path))
    {
        _textures[id] = texture;
    }
}

/**
    @brief Loads in a font from the filesystem.

    @param id The font's ID
    @param path Path to the font
 */
void AssetManager::loadFont(const std::string& id, const std::string& path)
{
    sf::Font font;

    if (font.loadFromFile(path))
    {
        _fonts[id] = font;
    }
}

/**
    @brief Retrieves a loaded texture.

    @param id The texture's ID
    @return sf::Texture&
 */
sf::Texture& AssetManager::getTexture(const std::string& id)
{
    return _textures.at(id);
}

/**
    @brief Retrieves a loaded font.

    @param id The font's ID
    @return sf::Font&
 */
sf::Font& AssetManager::getFont(const std::string& id)
{
    return _fonts.at(id);
}

}
