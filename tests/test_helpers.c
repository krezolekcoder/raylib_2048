#include "test_helpers.h"
#include "core_2048.h"
#include <stdio.h>


void test_helpers_set_tile_score(uint8_t x_coord, uint8_t y_coord, uint32_t score)
{
    game_tile_t *game_tile = core_2048_get_tile(x_coord, y_coord);

    game_tile->score = score;
}


void test_helpers_print_score_grid(void)
{
    printf("\r\n");
    for (int y_coord = 0; y_coord < 4; y_coord++) {
        for (int x_coord = 0; x_coord < 4; x_coord++) {
            game_tile_t *game_tile = core_2048_get_tile(x_coord, y_coord);

            printf("%d ", game_tile->score);
        }
        printf("\r\n");
    }
}