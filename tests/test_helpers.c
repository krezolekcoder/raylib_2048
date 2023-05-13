#include "test_helpers.h"
#include "core_2048.h"



void set_tile_score(uint8_t x_coord, uint8_t y_coord, uint32_t score)
{
    game_tile_t *game_tile = core_2048_get_tile(x_coord, y_coord);

    game_tile->score = score;
}