#ifndef __GAME_H__
#define __GAME_H__

#include "AssetManager.hpp"
#include "Defs.hpp"
#include "InputManager.hpp"
#include "SceneManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace Daft
{

struct Context
{
    sf::RenderWindow window;
    SceneManager sceneMgr;
    AssetManager assetMgr;
    InputManager inputMgr;
};

typedef std::shared_ptr<Context> ContextRef;

class Game
{
private:
    ContextRef _context = std::make_shared<Context>();
    const float _dt = GAME_DT;
    sf::Clock _clock;

public:
    Game(int width, int height, const std::string& title);
    int run();
};

} // namespace Daft

#endif /* __GAME_H__ */
