#ifndef __ASSETMANAGER_H__
#define __ASSETMANAGER_H__

#include <SFML/Graphics.hpp>
#include <map>

namespace Daft
{

class AssetManager
{
private:
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::Font> _fonts;

public:
    void loadTexture(const std::string& id, const std::string& path);
    void loadFont(const std::string& id, const std::string& path);

    sf::Texture& getTexture(const std::string& id);
    sf::Font& getFont(const std::string& id);
};

}

#endif /* __ASSETMANAGER_H__ */
