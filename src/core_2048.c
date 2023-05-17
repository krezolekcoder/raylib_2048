#include "core_2048.h"
#include "colors_palette.h"
#include "config.h"
#include "platform_port.h"

static game_tile_t prv_game_tiles[TILE_CNT_ROW][TILE_CNT_ROW];

static bool prv_is_movement_possible(movement_type_t movement);

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

bool core_2048_movement_update(movement_type_t movement)
{
    uint32_t tile_movement_counter = 0;

    switch (movement) {
    case MOVEMENT_UP:
        for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
            for (int y_tile_pos = 1; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
                for (int y_shift_movement = y_tile_pos - 1; y_shift_movement >= 0; y_shift_movement--) {

                    if (prv_game_tiles[y_shift_movement][x_tile_pos].score == 0) {
                        prv_game_tiles[y_shift_movement][x_tile_pos].score =
                            prv_game_tiles[y_shift_movement + 1][x_tile_pos].score;
                        prv_game_tiles[y_shift_movement + 1][x_tile_pos].score = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles[y_shift_movement + 1][x_tile_pos].score ==
                             prv_game_tiles[y_shift_movement][x_tile_pos].score) {
                        prv_game_tiles[y_shift_movement][x_tile_pos].score +=
                            prv_game_tiles[y_shift_movement + 1][x_tile_pos].score;
                        prv_game_tiles[y_shift_movement + 1][x_tile_pos].score = 0;
                        tile_movement_counter++;
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
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles[y_shift_movement + 1][x_tile_pos].score ==
                             prv_game_tiles[y_shift_movement][x_tile_pos].score) {
                        prv_game_tiles[y_shift_movement + 1][x_tile_pos].score +=
                            prv_game_tiles[y_shift_movement][x_tile_pos].score;
                        prv_game_tiles[y_shift_movement][x_tile_pos].score = 0;
                        tile_movement_counter++;
                    }
                }
            }
        }

        break;

    case MOVEMENT_LEFT:

        printf("MOVEMENT");
        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
            for (int x_tile_pos = 1; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                for (int x_shift_movement = x_tile_pos - 1; x_shift_movement >= 0; x_shift_movement--) {

                    if (prv_game_tiles[y_tile_pos][x_shift_movement].score == 0 &&
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score != 0) {
                        prv_game_tiles[y_tile_pos][x_shift_movement].score =
                            prv_game_tiles[y_tile_pos][x_shift_movement + 1].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score = 0;
                        tile_movement_counter++;
                    }
                    else if ((prv_game_tiles[y_tile_pos][x_shift_movement + 1].score ==
                              prv_game_tiles[y_tile_pos][x_shift_movement].score) &&
                             prv_game_tiles[y_tile_pos][x_shift_movement].score != 0) {
                        prv_game_tiles[y_tile_pos][x_shift_movement].score +=
                            prv_game_tiles[y_tile_pos][x_shift_movement + 1].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score = 0;
                        tile_movement_counter++;
                    }
                }
            }
        }


        break;

    case MOVEMENT_RIGHT:

        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
            for (int x_tile_pos = 2U; x_tile_pos >= 0; x_tile_pos--) {
                for (int x_shift_movement = x_tile_pos; x_shift_movement < TILE_CNT_ROW - 1; x_shift_movement++) {

                    if (prv_game_tiles[y_tile_pos][x_shift_movement + 1].score == 0 &&
                        prv_game_tiles[y_tile_pos][x_shift_movement].score != 0) {
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score =
                            prv_game_tiles[y_tile_pos][x_shift_movement].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement].score = 0;
                        tile_movement_counter++;
                    }
                    else if ((prv_game_tiles[y_tile_pos][x_shift_movement + 1].score ==
                              prv_game_tiles[y_tile_pos][x_shift_movement].score) &&
                             prv_game_tiles[y_tile_pos][x_shift_movement].score != 0U) {
                        prv_game_tiles[y_tile_pos][x_shift_movement + 1].score +=
                            prv_game_tiles[y_tile_pos][x_shift_movement].score;
                        prv_game_tiles[y_tile_pos][x_shift_movement].score = 0;
                        tile_movement_counter++;
                    }
                }
            }
        }

        break;
    default:
        break;
    }

    return tile_movement_counter != 0 ? true : false;
}

game_tile_t *core_2048_get_tile(uint32_t x_coord, uint32_t y_coord)
{
    if (x_coord >= TILE_CNT_ROW || y_coord >= TILE_CNT_ROW) {
        return NULL;
    }

    return &prv_game_tiles[y_coord][x_coord];
}
