#ifndef __MINESCENE_H__
#define __MINESCENE_H__

#include "Game.hpp"
#include <SFML/Graphics.hpp>

namespace Daft
{

enum CellState
{
    Unclicked,
    Flagged,
    Clicked,
    Mine,
    MineTripped,
};

struct Cell
{
    sf::Sprite sprite;
    CellState state;
    int y;
    int x;
    bool isMine = false;
    int surroundingMines = 0;
    sf::Text text;
};

class MineScene : public Scene
{
private:
    ContextRef _context;
    std::vector<Cell> _grid;

    bool _isGameOver = false;

public:
    MineScene(ContextRef context);

    void init();
    void poll();
    void update(float dt);
    void render(float dt);

private:
    void populateMines();
    void getMineNumbers();
    void getMinesAroundCell(Cell& cell);
    void setCell(Cell& cell, CellState state);
    void revealCell(Cell& cell);
    void gameOver();
    void revealAllCells();
    void handleCellClickEvent();
};

}

#endif /* __MINESCENE_H__ */
