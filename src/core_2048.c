#include "core_2048.h"
#include "colors_palette.h"
#include "config.h"
#include "platform_port.h"

static game_tile_score_t prv_game_tiles_score[TILE_CNT_ROW][TILE_CNT_ROW];

void core_2048_tiles_init(uint32_t first_tile_init_pos, uint32_t second_tile_init_pos)
{

    for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {

            uint32_t tile_coord = x_tile_pos * TILE_CNT_ROW + y_tile_pos;
            if (tile_coord == first_tile_init_pos || tile_coord == second_tile_init_pos) {
                prv_game_tiles_score[x_tile_pos][y_tile_pos] = 2;
            }
            else {
                prv_game_tiles_score[x_tile_pos][y_tile_pos] = 0;
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

                    if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] == 0) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_shift_movement][x_tile_pos] == 0) {
                        prv_game_tiles_score[y_shift_movement][x_tile_pos] =
                            prv_game_tiles_score[y_shift_movement + 1][x_tile_pos];
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] ==
                             prv_game_tiles_score[y_shift_movement][x_tile_pos]) {
                        prv_game_tiles_score[y_shift_movement][x_tile_pos] +=
                            prv_game_tiles_score[y_shift_movement + 1][x_tile_pos];
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] = 0;
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

                    if (prv_game_tiles_score[y_shift_movement][x_tile_pos] == 0U) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] == 0) {
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] =
                            prv_game_tiles_score[y_shift_movement][x_tile_pos];
                        prv_game_tiles_score[y_shift_movement][x_tile_pos] = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] ==
                             prv_game_tiles_score[y_shift_movement][x_tile_pos]) {
                        prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] +=
                            prv_game_tiles_score[y_shift_movement][x_tile_pos];
                        prv_game_tiles_score[y_shift_movement][x_tile_pos] = 0;
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

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] == 0) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement] == 0) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement] =
                            prv_game_tiles_score[y_tile_pos][x_shift_movement + 1];
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] ==
                             prv_game_tiles_score[y_tile_pos][x_shift_movement]) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement] +=
                            prv_game_tiles_score[y_tile_pos][x_shift_movement + 1];
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] = 0;
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

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement] == 0) {
                        continue;
                    }

                    if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] == 0) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] =
                            prv_game_tiles_score[y_tile_pos][x_shift_movement];
                        prv_game_tiles_score[y_tile_pos][x_shift_movement] = 0;
                        tile_movement_counter++;
                    }
                    else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] ==
                             prv_game_tiles_score[y_tile_pos][x_shift_movement]) {
                        prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] +=
                            prv_game_tiles_score[y_tile_pos][x_shift_movement];
                        prv_game_tiles_score[y_tile_pos][x_shift_movement] = 0;
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


bool core_2048_check_gameover_condition(void)
{

    uint32_t tile_movement_counter = 0;

    for (movement_type_t movement = MOVEMENT_UP; movement < MOVEMENT_CNT; movement++) {
        switch (movement) {
        case MOVEMENT_UP:
            for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                for (int y_tile_pos = 1; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
                    for (int y_shift_movement = y_tile_pos - 1; y_shift_movement >= 0; y_shift_movement--) {

                        if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] == 0) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_shift_movement][x_tile_pos] == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] ==
                                 prv_game_tiles_score[y_shift_movement][x_tile_pos]) {

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

                        if (prv_game_tiles_score[y_shift_movement][x_tile_pos] == 0U) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos] ==
                                 prv_game_tiles_score[y_shift_movement][x_tile_pos]) {
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

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] == 0) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement] == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] ==
                                 prv_game_tiles_score[y_tile_pos][x_shift_movement]) {
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

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement] == 0) {
                            continue;
                        }

                        if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] == 0) {
                            tile_movement_counter++;
                        }
                        else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1] ==
                                 prv_game_tiles_score[y_tile_pos][x_shift_movement]) {
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

game_tile_score_t core_2048_get_tile_score(uint32_t x_coord, uint32_t y_coord)
{
    if (x_coord >= TILE_CNT_ROW || y_coord >= TILE_CNT_ROW) {
        return UINT32_MAX;
    }

    return prv_game_tiles_score[y_coord][x_coord];
}


void core_2048_set_tile_score(uint32_t x_coord, uint32_t y_coord, uint32_t score)
{
    prv_game_tiles_score[y_coord][x_coord] = score;
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

            if (prv_game_tiles_score[y_tile][x_tile] == 0) {

                coords[coords_pair_idx].x = x_tile;
                coords[coords_pair_idx].y = y_tile;

                coords_pair_idx++;

                printf("PAIR %d X : %d  Y: %d \r\n", coords_pair_idx, x_tile, y_tile);
            }
        }
    }

    uint32_t random_idx = platform_port_get_random_nbr(0U, coords_pair_idx);

    // printf("RANDOM IDX : %d x_coord %d y_coord %d \r\n", random_idx, coords[random_idx].x,
    //        coords[random_idx].y);

    *x_coord = coords[random_idx].x;
    *y_coord = coords[random_idx].y;
}