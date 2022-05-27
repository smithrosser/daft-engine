#ifndef __SCENE_H__
#define __SCENE_H__

namespace Daft
{

struct Scene
{
    virtual void init() = 0;
    virtual void poll() = 0;
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;

    virtual void pause()
    {
    }

    virtual void resume()
    {
    }
};

} // namespace Daft

#endif /* __SCENE_H__ */
