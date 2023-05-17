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


typedef uint32_t game_tile_score_t;

void              core_2048_tiles_init(uint32_t first_tile_init_pos, uint32_t second_tile_init_pos);
bool              core_2048_movement_update(movement_type_t movement);
bool              core_2048_check_gameover_condition(void);
game_tile_score_t core_2048_get_tile_score(uint32_t x_coord, uint32_t y_coord);
void              core_2048_set_tile_score(uint32_t x_coord, uint32_t y_coord, uint32_t score);
void              core_2048_get_random_free_tile_coords(uint32_t *x_coord, uint32_t *y_coord);

#endif /* CORE_2048_H */
