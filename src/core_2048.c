#include "core_2048.h"
#include "colors_palette.h"
#include "config.h"
#include "platform_port.h"

typedef struct {
    uint32_t score;
    bool     merged;
} tile_t;

static tile_t prv_game_tiles_score[TILE_CNT_ROW][TILE_CNT_ROW];

static void prv_copy_score_buffer(movement_type_t movement, uint8_t row_col_nbr, tile_t score_buffer[4]);
static void prv_update_tiles_shift(tile_t loc_tiles[4]);
static void prv_update_score_buffer(movement_type_t movement, uint8_t row_col_nbr, tile_t score_buffer[4]);



bool core_2048_movement_update(movement_type_t movement)
{
    tile_t loc_tiles[4] = { [0].score = 0, [1].score = 0, [2].score = 0, [3].score = 0 };

    for (int row_col_idx = 0U; row_col_idx < TILE_CNT_ROW; row_col_idx++) {
        prv_copy_score_buffer(movement, row_col_idx, loc_tiles);

        prv_update_tiles_shift(loc_tiles);

        prv_update_score_buffer(movement, row_col_idx, loc_tiles);
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

static void prv_update_tiles_shift(tile_t loc_tiles[4])
{
    for (int tile_pos = 2U; tile_pos >= 0; tile_pos--) {
        for (int tile_movement = tile_pos; tile_movement < 3; tile_movement++) {
            if (loc_tiles[tile_movement + 1].score == 0) {
                loc_tiles[tile_movement + 1].score = loc_tiles[tile_movement].score;
                loc_tiles[tile_movement].score     = 0;
            }
            else if ((loc_tiles[tile_movement + 1].score == loc_tiles[tile_movement].score) &&
                     (loc_tiles[tile_movement + 1].merged == false && loc_tiles[tile_movement].merged == false)) {

                loc_tiles[tile_movement + 1].score += loc_tiles[tile_movement].score;
                loc_tiles[tile_movement + 1].merged = true;
                loc_tiles[tile_movement].score      = 0;
            }
        }
    }
}


static void prv_copy_score_buffer(movement_type_t movement, uint8_t row_col_nbr, tile_t score_buffer[4])
{
    switch (movement) {

    case MOVEMENT_UP:
        score_buffer[0].score = prv_game_tiles_score[3][row_col_nbr].score;
        score_buffer[1].score = prv_game_tiles_score[2][row_col_nbr].score;
        score_buffer[2].score = prv_game_tiles_score[1][row_col_nbr].score;
        score_buffer[3].score = prv_game_tiles_score[0][row_col_nbr].score;
        break;

    case MOVEMENT_DOWN:

        score_buffer[0].score = prv_game_tiles_score[0][row_col_nbr].score;
        score_buffer[1].score = prv_game_tiles_score[1][row_col_nbr].score;
        score_buffer[2].score = prv_game_tiles_score[2][row_col_nbr].score;
        score_buffer[3].score = prv_game_tiles_score[3][row_col_nbr].score;
        break;

    case MOVEMENT_LEFT:

        score_buffer[0].score = prv_game_tiles_score[row_col_nbr][3].score;
        score_buffer[1].score = prv_game_tiles_score[row_col_nbr][2].score;
        score_buffer[2].score = prv_game_tiles_score[row_col_nbr][1].score;
        score_buffer[3].score = prv_game_tiles_score[row_col_nbr][0].score;

        break;

    case MOVEMENT_RIGHT:
        score_buffer[0].score = prv_game_tiles_score[row_col_nbr][0].score;
        score_buffer[1].score = prv_game_tiles_score[row_col_nbr][1].score;
        score_buffer[2].score = prv_game_tiles_score[row_col_nbr][2].score;
        score_buffer[3].score = prv_game_tiles_score[row_col_nbr][3].score;
        break;

    default:
        break;
    }
}

static void prv_update_score_buffer(movement_type_t movement, uint8_t row_col_nbr, tile_t score_buffer[4])
{
    switch (movement) {

    case MOVEMENT_UP:
        prv_game_tiles_score[3][row_col_nbr].score = score_buffer[0].score;
        prv_game_tiles_score[2][row_col_nbr].score = score_buffer[1].score;
        prv_game_tiles_score[1][row_col_nbr].score = score_buffer[2].score;
        prv_game_tiles_score[0][row_col_nbr].score = score_buffer[3].score;
        break;

    case MOVEMENT_DOWN:
        prv_game_tiles_score[0][row_col_nbr].score = score_buffer[0].score;
        prv_game_tiles_score[1][row_col_nbr].score = score_buffer[1].score;
        prv_game_tiles_score[2][row_col_nbr].score = score_buffer[2].score;
        prv_game_tiles_score[3][row_col_nbr].score = score_buffer[3].score;
        break;

    case MOVEMENT_LEFT:

        prv_game_tiles_score[row_col_nbr][3].score = score_buffer[0].score;
        prv_game_tiles_score[row_col_nbr][2].score = score_buffer[1].score;
        prv_game_tiles_score[row_col_nbr][1].score = score_buffer[2].score;
        prv_game_tiles_score[row_col_nbr][0].score = score_buffer[3].score;
        break;

    case MOVEMENT_RIGHT:

        prv_game_tiles_score[row_col_nbr][0].score = score_buffer[0].score;
        prv_game_tiles_score[row_col_nbr][1].score = score_buffer[1].score;
        prv_game_tiles_score[row_col_nbr][2].score = score_buffer[2].score;
        prv_game_tiles_score[row_col_nbr][3].score = score_buffer[3].score;

        break;

    default:
        break;
    }
}


// bool core_2048_movement_update(movement_type_t movement)
// {
//     uint32_t tile_movement_counter = 0;

//     switch (movement) {
//     case MOVEMENT_UP:
//         for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
//             for (int y_tile_pos = 1; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
//                 for (int y_shift_movement = y_tile_pos - 1; y_shift_movement >= 0; y_shift_movement--) {

//                     if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score == 0) {
//                         continue;
//                     }

//                     if (prv_game_tiles_score[y_shift_movement][x_tile_pos].score == 0) {
//                         prv_game_tiles_score[y_shift_movement][x_tile_pos].score =
//                             prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score;
//                         prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score = 0;
//                         tile_movement_counter++;
//                     }
//                     else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score ==
//                              prv_game_tiles_score[y_shift_movement][x_tile_pos].score) {
//                         prv_game_tiles_score[y_shift_movement][x_tile_pos].score +=
//                             prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score;
//                         prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score = 0;
//                         tile_movement_counter++;
//                     }
//                 }
//             }
//         }

//         break;

//     case MOVEMENT_DOWN:

//         for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
//             for (int y_tile_pos = 2U; y_tile_pos >= 0; y_tile_pos--) {
//                 for (int y_shift_movement = y_tile_pos; y_shift_movement < TILE_CNT_ROW - 1; y_shift_movement++) {

//                     if (prv_game_tiles_score[y_shift_movement][x_tile_pos].score == 0U) {
//                         continue;
//                     }

//                     if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score == 0) {
//                         prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score =
//                             prv_game_tiles_score[y_shift_movement][x_tile_pos].score;
//                         prv_game_tiles_score[y_shift_movement][x_tile_pos].score = 0;
//                         tile_movement_counter++;
//                     }
//                     else if (prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score ==
//                              prv_game_tiles_score[y_shift_movement][x_tile_pos].score) {
//                         prv_game_tiles_score[y_shift_movement + 1][x_tile_pos].score +=
//                             prv_game_tiles_score[y_shift_movement][x_tile_pos].score;
//                         prv_game_tiles_score[y_shift_movement][x_tile_pos].score = 0;
//                         tile_movement_counter++;
//                     }
//                 }
//             }
//         }

//         break;

//     case MOVEMENT_LEFT:

//         for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
//             for (int x_tile_pos = 1; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
//                 for (int x_shift_movement = x_tile_pos - 1; x_shift_movement >= 0; x_shift_movement--) {

//                     if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score == 0) {
//                         continue;
//                     }

//                     if (prv_game_tiles_score[y_tile_pos][x_shift_movement].score == 0) {
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement].score =
//                             prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score;
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score = 0;
//                         tile_movement_counter++;
//                     }
//                     else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score ==
//                              prv_game_tiles_score[y_tile_pos][x_shift_movement].score) {
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement].score +=
//                             prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score;
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score = 0;
//                         tile_movement_counter++;
//                     }
//                 }
//             }
//         }


//         break;

//     case MOVEMENT_RIGHT:

//         for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
//             for (int x_tile_pos = 2U; x_tile_pos >= 0; x_tile_pos--) {
//                 for (int x_shift_movement = x_tile_pos; x_shift_movement < TILE_CNT_ROW - 1; x_shift_movement++) {

//                     if (prv_game_tiles_score[y_tile_pos][x_shift_movement].score == 0) {
//                         continue;
//                     }

//                     if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score == 0) {
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score =
//                             prv_game_tiles_score[y_tile_pos][x_shift_movement].score;
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement].score = 0;
//                         tile_movement_counter++;
//                     }
//                     else if (prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score ==
//                              prv_game_tiles_score[y_tile_pos][x_shift_movement].score) {
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement + 1].score +=
//                             prv_game_tiles_score[y_tile_pos][x_shift_movement].score;
//                         prv_game_tiles_score[y_tile_pos][x_shift_movement].score = 0;
//                         tile_movement_counter++;
//                     }
//                 }
//             }
//         }

//         break;
//     default:
//         break;
//     }

//     return tile_movement_counter != 0 ? true : false;
// }
