#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.hpp"
#include <memory>
#include <stack>

namespace Daft
{

typedef std::unique_ptr<Scene> SceneRef;

enum SceneManagerState
{
    Ready,
    Adding,
    Replacing,
    Removing,
};

class SceneManager
{
private:
    std::stack<SceneRef> _scenes;
    SceneRef _newScene;
    SceneManagerState _state = SceneManagerState::Ready;

public:
    void push(SceneRef newScene, bool isReplacing = true);
    void pop();
    SceneRef& peek();

    void update();
};

} // namespace Daft

#endif /* __SCENEMANAGER_H__ */
