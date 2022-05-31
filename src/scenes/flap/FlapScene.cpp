#include "FlapScene.hpp"
#include <iostream>

namespace Daft
{

void FlapScene::init()
{
    std::srand(std::time(nullptr));

    _context->assetMgr.loadTexture("birdUp", BIRD_UP_PATH);
    _context->assetMgr.loadTexture("birdDown", BIRD_DOWN_PATH);
    _context->assetMgr.loadTexture("birdDead", BIRD_DEAD_PATH);
    _context->assetMgr.loadTexture("pipe", PIPE_PATH);
    _context->assetMgr.loadTexture("cloud", CLOUD_PATH);
    _context->assetMgr.loadFont("text", FONT_PATH);

    // bird
    _bird.vel = { 0, 0 };
    _bird.sprite.setTexture(_context->assetMgr.getTexture("birdDown"));
    _bird.sprite.setPosition(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
    _bird.sprite.setScale(BIRD_SCALE, BIRD_SCALE);

    // game over text
    _gameOverText.setFont(_context->assetMgr.getFont("text"));
    _gameOverText.setCharacterSize(84);
    _gameOverText.setOutlineColor(sf::Color::Black);
    _gameOverText.setOutlineThickness(4);
    _gameOverText.setPosition(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 40);
    _gameOverText.setString(":(");

    // score text
    _scoreText.setFont(_context->assetMgr.getFont("text"));
    _scoreText.setCharacterSize(40);
    _scoreText.setOutlineColor(sf::Color::Black);
    _scoreText.setOutlineThickness(2);
    _scoreText.setPosition(0.05f * SCREEN_WIDTH, 0.05f * SCREEN_HEIGHT);
    _scoreText.setString(std::to_string(_score));

    createPipe();
    createCloud();
}

void FlapScene::poll()
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
        case sf::Event::KeyPressed:
        {
            if (!_isGameOver && event.key.code == sf::Keyboard::Up)
            {
                _bird.flap();
            }
            else if (_isGameOver && event.key.code == sf::Keyboard::Enter)
            {
                _context->sceneMgr.push(SceneRef(new FlapScene(_context)));
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void FlapScene::update(float dt)
{
    if (!_isGameOver)
    {
        // move the pipes towards the player
        for (auto& pipe : _pipes)
        {
            pipe.move(dt);

            if (pipe.pos.x < SCREEN_WIDTH / 2.f && pipe.bSpawnNewPipe)
            {
                createPipe();
                pipe.bSpawnNewPipe = false;
            }
        }

        // delete pipes from list when off screen
        if (_pipes.front().pos.x <= -64.f)
        {
            _pipes.pop_front();
        }

        _bird.fall(dt);
        if (_bird.vel.y < 0)
        {
            _bird.setTexture(_context->assetMgr.getTexture("birdUp"));
        }
        else if (_bird.vel.y >= 0)
        {
            _bird.setTexture(_context->assetMgr.getTexture("birdDown"));
        }

        // kill bird if it bottoms out
        if (_bird.sprite.getGlobalBounds().contains(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT))
        {
            gameOver();
        }

        // pipe handling
        Pipe& nearestPipe = _pipes.front();

        if (nearestPipe.pos.x <= SCREEN_WIDTH / 3.f)
        {
            sf::FloatRect bird = _bird.sprite.getGlobalBounds();
            sf::FloatRect upperPipe = nearestPipe.upper.getGlobalBounds();
            sf::FloatRect lowerPipe = nearestPipe.lower.getGlobalBounds();

            if (upperPipe.intersects(bird) || lowerPipe.intersects(bird))
            {
                gameOver();
            }

            if ((upperPipe.left + upperPipe.width) <= bird.left && !nearestPipe.bScored)
            {
                incrementScore();
                nearestPipe.bScored = true;
            }
        }
    }
}

void FlapScene::render(float dt)
{
    _context->window.clear(sf::Color(150, 213, 242));

    for (auto& cloud : _clouds)
    {
        _context->window.draw(cloud);
    }
    for (auto& pipe : _pipes)
    {
        _context->window.draw(pipe.upper);
        _context->window.draw(pipe.lower);
    }
    _context->window.draw(_bird.sprite);

    _context->window.draw(_scoreText);

    if (_isGameOver)
    {
        _context->window.draw(_gameOverText);
    }

    _context->window.display();
}

void FlapScene::createPipe()
{
    Pipe newPipe;

    newPipe.upper.setTexture(_context->assetMgr.getTexture("pipe"));
    newPipe.lower.setTexture(_context->assetMgr.getTexture("pipe"));

    _pipes.push_back(newPipe);
}

void FlapScene::createCloud()
{

    for (auto& cloud : _clouds)
    {
        cloud.setTexture(_context->assetMgr.getTexture("cloud"));
        cloud.setScale(2.0f, 2.0f);
    }

    _clouds[0].setPosition(10, 80);
    _clouds[1].setPosition(80, 10);
    _clouds[2].setPosition(220, 40);
}

void FlapScene::incrementScore()
{
    _score++;
    _scoreText.setString(std::to_string(_score));
}

void FlapScene::gameOver()
{
    _isGameOver = true;
    _gameOverTime = _clock.getElapsedTime().asSeconds();

    _bird.sprite.setTexture(_context->assetMgr.getTexture("birdDead"));
}

}
