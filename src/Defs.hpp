#ifndef __DEFS_H__
#define __DEFS_H__

constexpr float GAME_MAX_FPS = 60.0f;
constexpr float GAME_DT = 1.0f / GAME_MAX_FPS;

constexpr int CELL_SCALE = 2;
constexpr int CELL_SIZE = 16 * CELL_SCALE;
constexpr int GRID_COLS = 10;
constexpr int GRID_ROWS = 10;
constexpr int N_MINES = 15;

constexpr int SCREEN_WIDTH = GRID_COLS * CELL_SIZE;
constexpr int SCREEN_HEIGHT = GRID_ROWS * CELL_SIZE;

#define UNCLICKED_PATH "../res/img/unclicked.png"
#define FLAGGED_PATH "../res/img/flagged.png"
#define CLICKED_PATH "../res/img/clicked.png"
#define MINE_PATH "../res/img/mine.png"
#define TRIPPED_PATH "../res/img/tripped.png"

#define FONT_PATH "../res/fonts/slkscr.ttf"

#endif /* __DEFS_H__ */
