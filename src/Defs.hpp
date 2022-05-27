#ifndef __DEFS_H__
#define __DEFS_H__

constexpr float GAME_MAX_FPS = 60.0f;
constexpr float GAME_DT = 1.0f / GAME_MAX_FPS;

constexpr int CELL_SIZE = 32;
constexpr int GRID_COLS = 30;
constexpr int GRID_ROWS = 20;

constexpr int SCREEN_WIDTH = GRID_COLS * CELL_SIZE;
constexpr int SCREEN_HEIGHT = GRID_ROWS * CELL_SIZE;

#endif /* __DEFS_H__ */
