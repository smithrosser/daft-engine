#include "MineScene.hpp"
#include "Defs.hpp"
#include <iostream>

namespace Daft
{

MineScene::MineScene(ContextRef context)
    : _context(context)
{
}

void MineScene::init()
{
    _context->assetMgr.loadTexture("unclicked", UNCLICKED_PATH);
    _context->assetMgr.loadTexture("flagged", FLAGGED_PATH);
    _context->assetMgr.loadTexture("clicked", CLICKED_PATH);
    _context->assetMgr.loadTexture("mine", MINE_PATH);
    _context->assetMgr.loadTexture("tripped", TRIPPED_PATH);
    _context->assetMgr.loadFont("numbers", FONT_PATH);

    for (int y = 0; y < GRID_ROWS; y++)
    {
        for (int x = 0; x < GRID_COLS; x++)
        {
            Cell cell;

            cell.y = y;
            cell.x = x;
            cell.state = CellState::Unclicked;
            cell.sprite.setTexture(_context->assetMgr.getTexture("unclicked"));
            cell.sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            cell.sprite.setScale(CELL_SCALE, CELL_SCALE);
            cell.text.setFont(_context->assetMgr.getFont("numbers"));
            cell.text.setCharacterSize(24);
            cell.text.setPosition(x * CELL_SIZE + (CELL_SIZE / 4), y * CELL_SIZE);

            _grid.push_back(cell);
        }
    }

    populateMines();
    getMineNumbers();
}

void MineScene::poll()
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
        case sf::Event::MouseButtonPressed:
        {
            handleCellClickEvent();
            break;
        }
        }
    }
}

void MineScene::update(float dt)
{
}

void MineScene::render(float dt)
{
    _context->window.clear();

    for (auto& cell : _grid)
    {
        _context->window.draw(cell.sprite);
        if (cell.state == CellState::Clicked)
        {
            _context->window.draw(cell.text);
        }
    }

    _context->window.display();
}

void MineScene::populateMines()
{
    const int gridSize = GRID_COLS * GRID_ROWS;

    std::srand(std::time(nullptr));

    for (int i = 0; i < N_MINES; i++)
    {
        int randIdx = std::rand() % gridSize;

        while (!_grid[randIdx].isMine)
        {
            if (!_grid[randIdx].isMine)
            {
                _grid[randIdx].isMine = true;
            }
            else
            {
                randIdx = std::rand() % gridSize;
            }
        }
    }
}

void MineScene::getMineNumbers(void)
{
    for (auto& cell : _grid)
    {
        getMinesAroundCell(cell);
    }
}

void MineScene::getMinesAroundCell(Cell& cell)
{
    int mineCount = 0;

    if (!cell.isMine)
    {
        for (int y = cell.y - 1; y <= cell.y + 1; y++)
        {
            if (y < 0)
                continue;
            if (y >= GRID_ROWS)
                break;

            for (int x = cell.x - 1; x <= cell.x + 1; x++)
            {
                if (x < 0)
                    continue;
                if (x >= GRID_COLS)
                    break;
                if (x == cell.x && y == cell.y)
                    continue;

                // add 1 to mine count if a mine
                if (_grid[y * GRID_COLS + x].isMine)
                {
                    mineCount++;
                }
            }
        }
    }

    cell.surroundingMines = mineCount;
    cell.text.setString((mineCount > 0) ? std::to_string(mineCount) : std::string(""));
}

void MineScene::revealCell(Cell& cell)
{
    if (cell.isMine)
    {
        setCell(cell, CellState::Mine);

        if (!_isGameOver)
        {
            setCell(cell, CellState::MineTripped);
            gameOver();
        }
    }
    else
    {
        setCell(cell, CellState::Clicked);
    }
}

void MineScene::gameOver()
{
    _isGameOver = true;

    for (auto& cell : _grid)
    {
        if (cell.state != CellState::MineTripped)
        {
            revealCell(cell);
        }
    }
}

void MineScene::setCell(Cell& cell, CellState state)
{
    cell.state = state;

    switch (cell.state)
    {
    case CellState::Unclicked:
        cell.sprite.setTexture(_context->assetMgr.getTexture("unclicked"));
        break;
    case CellState::Flagged:
        cell.sprite.setTexture(_context->assetMgr.getTexture("flagged"));
        break;
    case CellState::Clicked:
        cell.sprite.setTexture(_context->assetMgr.getTexture("clicked"));
        break;
    case CellState::Mine:
        cell.sprite.setTexture(_context->assetMgr.getTexture("mine"));
        break;
    case CellState::MineTripped:
        cell.sprite.setTexture(_context->assetMgr.getTexture("tripped"));
        break;
    default:
        break;
    }
}

void MineScene::handleCellClickEvent()
{
    // find cell mouse is in
    sf::Vector2i mousePos = _context->inputMgr.getMousePos(_context->window);
    mousePos.x /= CELL_SIZE;
    mousePos.y /= CELL_SIZE;

    // get cell
    Cell& cell = _grid[mousePos.y * GRID_COLS + mousePos.x];

    if (_context->inputMgr.isEntityClicked(cell.sprite, sf::Mouse::Left, _context->window))
    {
        if (cell.state != CellState::Clicked && cell.state != CellState::Flagged)
        {
            revealCell(cell);
        }
    }
    else if (_context->inputMgr.isEntityClicked(cell.sprite, sf::Mouse::Right, _context->window))
    {
        if (cell.state != CellState::Clicked)
        {
            if (cell.state == CellState::Unclicked)
            {
                setCell(cell, CellState::Flagged);
            }
            else if (cell.state == CellState::Flagged)
            {
                setCell(cell, CellState::Unclicked);
            }
        }
    }
}

}