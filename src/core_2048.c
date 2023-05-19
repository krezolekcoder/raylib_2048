#include "core_2048.h"
#include "colors_palette.h"
#include "config.h"
#include "platform_port.h"

typedef struct {
    uint32_t score;
    bool     merged;
} tile_t;

static tile_t prv_game_tiles_score[TILE_CNT_ROW][TILE_CNT_ROW];

void core_2048_tiles_init(uint32_t first_tile_init_pos, uint32_t second_tile_init_pos)
{

    for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {

            uint32_t tile_coord = x_tile_pos * TILE_CNT_ROW + y_tile_pos;
            if (tile_coord == first_tile_init_pos || tile_coord == second_tile_init_pos) {
                prv_game_tiles_score[x_tile_pos][y_tile_pos].score = 2;
            }
            else {
                prv_game_tiles_score[x_tile_pos][y_tile_pos].score = 0;
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

                    if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score == 0) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_shift_movement][x_tile_pos].score == 0) {
                        prv_game_tiles_score[y_shift_movement][x_tile_pos].score =
                            prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score;
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score ==
                             prv_game_tiles_score[y_shift_movement][x_tile_pos].score) {
                        prv_game_tiles_score[y_shift_movement][x_tile_pos].score +=
                            prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score;
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score = 0;
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

                    if (prv_game_tiles_score[y_shift_movement][x_tile_pos].score == 0U) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score == 0) {
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score =
                            prv_game_tiles_score[y_shift_movement][x_tile_pos].score;
                        prv_game_tiles_score[y_shift_movement][x_tile_pos].score = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score ==
                             prv_game_tiles_score[y_shift_movement][x_tile_pos].score) {
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score +=
                            prv_game_tiles_score[y_shift_movement][x_tile_pos].score;
                        prv_game_tiles_score[y_shift_movement][x_tile_pos].score = 0;
                        tile_movement_counter++;
                    }
                }
            }
        }

        break;

    case MOVEMENT_LEFT:

        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
            for (int x_tile_pos = 1; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                for (int x_shift_movement = x_tile_pos - 1; x_shift_movement >= 0; x_shift_movement--) {

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score == 0) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement].score == 0) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement].score =
                            prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score;
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score ==
                             prv_game_tiles_score[y_tile_pos][x_shift_movement].score) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement].score +=
                            prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score;
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score = 0;
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

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement].score == 0) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score == 0) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score =
                            prv_game_tiles_score[y_tile_pos][x_shift_movement].score;
                        prv_game_tiles_score[y_tile_pos][x_shift_movement].score = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score ==
                             prv_game_tiles_score[y_tile_pos][x_shift_movement].score) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score +=
                            prv_game_tiles_score[y_tile_pos][x_shift_movement].score;
                        prv_game_tiles_score[y_tile_pos][x_shift_movement].score = 0;
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


bool core_2048_movement_update_alternative(movement_type_t movement)
{

    for (int y_tile_pos = 0U; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
        for (int x_tile_pos = 2U; x_tile_pos >= 0; x_tile_pos--) {
            for (int x_shift_movement = x_tile_pos; x_shift_movement < 3; x_shift_movement++) {

                // printf("X tile : %d X SHIFT %d \r\n", x_tile_pos, x_shift_movement);
                if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score == 0) {
                    prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score =
                        prv_game_tiles_score[y_tile_pos][x_shift_movement].score;
                    prv_game_tiles_score[y_tile_pos][x_shift_movement].score = 0;
                }
                else if ((prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score ==
                          prv_game_tiles_score[y_tile_pos][x_shift_movement].score) &&
                         (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].merged == false &&
                          prv_game_tiles_score[y_tile_pos][x_shift_movement].merged == false)) {
                    // printf("\r\n MERGING ! : x %d %d ", x_shift_movement, x_shift_movement + 1);
                    prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score +=
                        prv_game_tiles_score[y_tile_pos][x_shift_movement].score;
                    prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].merged = true;
                    prv_game_tiles_score[y_tile_pos][x_shift_movement].score      = 0;
                }

                // printf("\r\n");
                // for (int i = 0; i < 4; i++) {
                //     printf("%d ", prv_game_tiles_score[y_tile_pos][i].merged);
                // }
            }
        }
        break;
    }
}


void core_2048_clear_merging_info(void)
{
    for (int y = 0; y < TILE_CNT_ROW; y++) {
        for (int x = 0; x < TILE_CNT_ROW; x++) {
            prv_game_tiles_score[y][x].merged = false;
        }
    }
}


bool core_2048_check_gameover_condition(void)
{

    uint32_t tile_movement_counter = 0;

    for (movement_type_t movement = MOVEMENT_UP; movement < MOVEMENT_CNT; movement++) {
        switch (movement) {
        case MOVEMENT_UP:
            for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                for (int y_tile_pos = 1; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
                    for (int y_shift_movement = y_tile_pos - 1; y_shift_movement >= 0; y_shift_movement--) {

                        if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score == 0) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_shift_movement][x_tile_pos].score == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score ==
                                 prv_game_tiles_score[y_shift_movement][x_tile_pos].score) {

                            tile_movement_counter++;
                        }
                    }
                }
            }

            break;

        case MOVEMENT_DOWN:

            for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                for (int y_tile_pos = 2U; y_tile_pos >= 0; y_tile_pos--) {
                    for (int y_shift_movement = y_tile_pos; y_shift_movement < TILE_CNT_ROW - 1;
                         y_shift_movement++) {

                        if (prv_game_tiles_score[y_shift_movement][x_tile_pos].score == 0U) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score ==
                                 prv_game_tiles_score[y_shift_movement][x_tile_pos].score) {
                            tile_movement_counter++;
                        }
                    }
                }
            }

            break;

        case MOVEMENT_LEFT:

            for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
                for (int x_tile_pos = 1; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                    for (int x_shift_movement = x_tile_pos - 1; x_shift_movement >= 0; x_shift_movement--) {

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score == 0) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement].score == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score ==
                                 prv_game_tiles_score[y_tile_pos][x_shift_movement].score) {
                            tile_movement_counter++;
                        }
                    }
                }
            }


            break;

        case MOVEMENT_RIGHT:

            for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
                for (int x_tile_pos = 2U; x_tile_pos >= 0; x_tile_pos--) {
                    for (int x_shift_movement = x_tile_pos; x_shift_movement < TILE_CNT_ROW - 1;
                         x_shift_movement++) {

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement].score == 0) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score ==
                                 prv_game_tiles_score[y_tile_pos][x_shift_movement].score) {
                            tile_movement_counter++;
                        }
                    }
                }
            }

            break;
        default:
            break;
        }
    }

    return tile_movement_counter == 0 ? true : false;
}

uint32_t core_2048_get_tile_score(uint32_t x_coord, uint32_t y_coord)
{
    if (x_coord >= TILE_CNT_ROW || y_coord >= TILE_CNT_ROW) {
        return UINT32_MAX;
    }

    return prv_game_tiles_score[y_coord][x_coord].score;
}


void core_2048_set_tile_score(uint32_t x_coord, uint32_t y_coord, uint32_t score)
{
    prv_game_tiles_score[y_coord][x_coord].score = score;
}


void core_2048_get_random_free_tile_coords(uint32_t *x_coord, uint32_t *y_coord)
{
    typedef struct {
        uint32_t x;
        uint32_t y;
    } coord_pair_t;

    coord_pair_t coords[16U];
    uint32_t     coords_pair_idx = 0U;
    for (uint32_t y_tile = 0; y_tile < TILE_CNT_ROW; y_tile++) {
        for (uint32_t x_tile = 0; x_tile < TILE_CNT_ROW; x_tile++) {

            if (prv_game_tiles_score[y_tile][x_tile].score == 0) {

                coords[coords_pair_idx].x = x_tile;
                coords[coords_pair_idx].y = y_tile;

                coords_pair_idx++;
            }
        }
    }

    uint32_t random_idx = platform_port_get_random_nbr(0U, coords_pair_idx - 1);

    *x_coord = coords[random_idx].x;
    *y_coord = coords[random_idx].y;
}