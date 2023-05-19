#ifndef CORE_2048_H
#define CORE_2048_H

#include "raylib.h"
#include <stdint.h>

#define MAX_KEY_MAPPINGS (3U)
#define KEYS_CNT         (4U)

typedef enum {
    MOVEMENT_UP = 0,
    MOVEMENT_DOWN,
    MOVEMENT_LEFT,
    MOVEMENT_RIGHT,
    MOVEMENT_CNT,
} movement_type_t;


bool     core_2048_movement_update(movement_type_t movement);
bool     core_2048_check_gameover_condition(void);
uint32_t core_2048_get_tile_score(uint32_t x_coord, uint32_t y_coord);
void     core_2048_set_tile_score(uint32_t x_coord, uint32_t y_coord, uint32_t score);
void     core_2048_get_random_free_tile_coords(uint32_t *x_coord, uint32_t *y_coord);
void     core_2048_clear_merging_info(void);

#endif /* CORE_2048_H */
