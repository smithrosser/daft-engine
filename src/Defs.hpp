#ifndef __DEFS_H__
#define __DEFS_H__

constexpr float GRAVITY = 9.81;

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

#define BIRD_UP_PATH "../res/img/bird_up.png"
#define BIRD_DOWN_PATH "../res/img/bird_down.png"
#define BIRD_DEAD_PATH "../res/img/bird_dead.png"
#define PIPE_PATH "../res/img/pipe.png"
#define CLOUD_PATH "../res/img/cloud.png"

constexpr int BIRD_SIZE = 16;
constexpr float BIRD_SCALE = 2.0f;
constexpr float BIRD_FLAP_VEL = 5.0f;

#endif /* __DEFS_H__ */
