#include "core_2048.h"
#include "colors_palette.h"
#include "config.h"
#include "platform_port.h"

static game_tile_t prv_game_tiles[TILE_CNT_ROW][TILE_CNT_ROW];

void core_2048_tiles_init(uint32_t first_tile_init_pos, uint32_t second_tile_init_pos)
{

    for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {

            prv_game_tiles[x_tile_pos][y_tile_pos].font_color = BLACK;

            if (x_tile_pos * TILE_CNT_ROW + y_tile_pos == first_tile_init_pos) {
                prv_game_tiles[x_tile_pos][y_tile_pos].tile_color = COLOR_2;
                prv_game_tiles[x_tile_pos][y_tile_pos].score      = 2;
            }
            else {
                prv_game_tiles[x_tile_pos][y_tile_pos].tile_color = COLOR_EMPTY;
                prv_game_tiles[x_tile_pos][y_tile_pos].score      = 0;
            }
        }
    }
}

void core_2048_movement_update(movement_type_t movement)
{
    switch (movement) {
    case MOVEMENT_UP:
        for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
            for (int y_tile_pos = 1; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
                for (int y_shift_movement = y_tile_pos - 1; y_shift_movement >= 0; y_shift_movement--) {

                    if (prv_game_tiles[y_shift_movement][x_tile_pos].score == 0) {
                        prv_game_tiles[y_shift_movement][x_tile_pos].score =
                            prv_game_tiles[y_shift_movement + 1][x_tile_pos].score;
                        prv_game_tiles[y_shift_movement + 1][x_tile_pos].score = 0;
                    }
                    else if (prv_game_tiles[y_shift_movement + 1][x_tile_pos].score ==
                             prv_game_tiles[y_shift_movement][x_tile_pos].score) {
                        prv_game_tiles[y_shift_movement][x_tile_pos].score +=
                            prv_game_tiles[y_shift_movement + 1][x_tile_pos].score;
                        prv_game_tiles[y_shift_movement + 1][x_tile_pos].score = 0;
                    }
                }
            }
        }

        break;

    case MOVEMENT_DOWN:

        for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
            for (int y_tile_pos = 2U; y_tile_pos >= 0; y_tile_pos--) {
                for (int y_shift_movement = y_tile_pos; y_shift_movement < TILE_CNT_ROW - 1; y_shift_movement++) {

                    if (prv_game_tiles[y_shift_movement + 1][x_tile_pos].score == 0) {
                        prv_game_tiles[y_shift_movement + 1][x_tile_pos].score =
                            prv_game_tiles[y_shift_movement][x_tile_pos].score;
                        prv_game_tiles[y_shift_movement][x_tile_pos].score = 0;
                    }
                    else if (prv_game_tiles[y_shift_movement + 1][x_tile_pos].score ==
                             prv_game_tiles[y_shift_movement][x_tile_pos].score) {
                        prv_game_tiles[y_shift_movement + 1][x_tile_pos].score +=
                            prv_game_tiles[y_shift_movement][x_tile_pos].score;
                        prv_game_tiles[y_shift_movement][x_tile_pos].score = 0;
                    }
                }
            }
        }

        break;

    case MOVEMENT_LEFT:

        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
            for (int x_tile_pos = 1; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                for (int x_shift_movement = x_tile_pos - 1; x_shift_movement >= 0; x_shift_movement--) {

                    if (prv_game_tiles[y_tile_pos][x_shift_movement].score == 0) {
                        prv_game_tiles[y_tile_pos][x_shift_movement].score =
                            prv_game_tiles[y_tile_pos][x_shift_movement + 1].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score = 0;
                    }
                    else if (prv_game_tiles[y_tile_pos][x_shift_movement + 1].score ==
                             prv_game_tiles[y_tile_pos][x_shift_movement].score) {
                        prv_game_tiles[y_tile_pos][x_shift_movement].score +=
                            prv_game_tiles[y_tile_pos][x_shift_movement + 1].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score = 0;
                    }
                }
            }
        }


        break;

    case MOVEMENT_RIGHT:

        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
            for (int x_tile_pos = 2U; x_tile_pos >= 0; x_tile_pos--) {
                for (int x_shift_movement = x_tile_pos; x_shift_movement < TILE_CNT_ROW - 1; x_shift_movement++) {

                    if (prv_game_tiles[y_tile_pos][x_shift_movement + 1].score == 0) {
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score =
                            prv_game_tiles[y_tile_pos][x_shift_movement].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement].score = 0;
                    }
                    else if (prv_game_tiles[y_tile_pos][x_shift_movement + 1].score ==
                             prv_game_tiles[y_tile_pos][x_shift_movement].score) {
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score +=
                            prv_game_tiles[y_tile_pos][x_shift_movement].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement].score = 0;
                    }
                }
            }
        }


        break;
    default:
        break;
    }
}


game_tile_t *core_2048_get_tile(uint32_t x_coord, uint32_t y_coord)
{
    if (x_coord >= TILE_CNT_ROW || y_coord >= TILE_CNT_ROW) {
        return NULL;
    }

    return &prv_game_tiles[y_coord][x_coord];
}



void core_2048_draw_grid(void)
{
    for (int i = 0; i < TILE_CNT_ROW; i++) {
        for (int j = 0; j < TILE_CNT_ROW; j++) {
            platform_port_draw_tile(prv_game_tiles[i][j].x_pos, prv_game_tiles[i][j].y_pos,
                                    prv_game_tiles[i][j].tile_color, prv_game_tiles[i][j].score,
                                    prv_game_tiles[i][j].font_color);
        }
    }
}
