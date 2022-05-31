#ifndef __BASICSCENE_H__
#define __BASICSCENE_H__

#include "Game.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

namespace Daft
{

class BasicScene : public Scene
{
private:
    ContextRef _context;

public:
    BasicScene(ContextRef context);
    ~BasicScene();

    virtual void init();
    virtual void poll();
    virtual void update(float dt);
    virtual void render(float dt);
};

}

#endif /* __BASICSCENE_H__ */
