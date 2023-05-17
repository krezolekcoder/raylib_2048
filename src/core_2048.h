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

typedef struct {
    uint32_t score;
    uint32_t x_pos;
    uint32_t y_pos;
    Color    tile_color;
    Color    font_color;
} game_tile_t;

typedef struct {
    KeyboardKey key_mappings[MAX_KEY_MAPPINGS];
} keyboard_mapping_t;


void         core_2048_tiles_init(uint32_t first_tile_init_pos, uint32_t second_tile_init_pos);
bool         core_2048_movement_update(movement_type_t movement);
bool         core_2048_check_gameover_condition(void);
void         core_2048_set_tile_result(uint8_t x_coord, uint8_t y_coord, uint32_t result);
game_tile_t *core_2048_get_tile(uint32_t x_coord, uint32_t y_coord);

#endif /* CORE_2048_H */
