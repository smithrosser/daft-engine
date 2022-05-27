#include "SceneManager.hpp"

namespace Daft
{

/**
    @brief Pushes a new scene to the scene stack.

    @param newScene The new scene
    @param isReplacing true: replace the current scene
 */
void SceneManager::push(SceneRef newScene, bool isReplacing)
{
    _newScene = std::move(newScene);
    _state = (isReplacing) ? SceneManagerState::Replacing : SceneManagerState::Adding;
}

/**
    @brief Pops the current scene from the scene stack.

 */
void SceneManager::pop()
{
    _state = SceneManagerState::Removing;
}

/**
    @brief Retrieves the current scene from the scene stack.

    @return SceneRef& The current scene.
 */
SceneRef& SceneManager::peek()
{
    return _scenes.top();
}

/**
    @brief Updates the scene stack state machine.

 */
void SceneManager::update()
{
    switch (_state)
    {
    case SceneManagerState::Removing:
    {
        if (!_scenes.empty())
        {
            _scenes.pop();

            if (!_scenes.empty())
            {
                _scenes.top()->resume();
            }
        }
        _state = SceneManagerState::Ready;

        break;
    }
    case SceneManagerState::Adding:
    case SceneManagerState::Replacing:
    {
        if (!_scenes.empty())
        {
            if (_state == SceneManagerState::Replacing)
            {
                _scenes.pop();
            }
            else
            {
                _scenes.top()->pause();
            }
        }
        _scenes.push(std::move(_newScene));
        _scenes.top()->init();

        _state = SceneManagerState::Ready;

        break;
    }
    case SceneManagerState::Ready:
    default:
    {
        break;
    }
    }
}

} // namespace Daft
