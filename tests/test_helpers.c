#include "test_helpers.h"
#include "core_2048.h"
#include <stdio.h>


void test_helpers_print_score_grid(void)
{
    printf("\r\n");
    for (int y_coord = 0; y_coord < 4; y_coord++) {
        for (int x_coord = 0; x_coord < 4; x_coord++) {

            printf("%d ", core_2048_get_tile_score(x_coord, y_coord));
        }
        printf("\r\n");
    }
}

void test_helpers_print_row(uint32_t *row, uint8_t size)
{
    printf("\r\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", row[i]);
    }
    printf("\r\n");
}

void test_helpers_clear_grid(void)
{
    core_2048_clear_merging_info();
    for (int y_coord = 0; y_coord < 4; y_coord++) {
        for (int x_coord = 0; x_coord < 4; x_coord++) {
            core_2048_set_tile_score(x_coord, y_coord, 0);
        }
    }
}