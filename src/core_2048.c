#include "core_2048.h"
#include "colors_palette.h"
#include "config.h"
#include "platform_port.h"

static const keyboard_mapping_t prv_keys_mapping[KEY_PRESSED_TYPES_CNT] = {
    [KEY_TYPE_UP].key_mappings    = {KEY_W,  KEY_UP,    KEY_KP_8},
    [KEY_TYPE_DOWN].key_mappings  = { KEY_S, KEY_DOWN,  KEY_KP_2},
    [KEY_TYPE_LEFT].key_mappings  = { KEY_A, KEY_LEFT,  KEY_KP_4},
    [KEY_TYPE_RIGHT].key_mappings = { KEY_D, KEY_RIGHT, KEY_KP_6},
};

static game_tile_t prv_game_tiles[SCREEN_WIDTH_BLOCK_CNT][SCREEN_HEIGHT_BLOCK_CNT];

static void prv_key_pressed_callback(key_pressed_types_t key_pressed_type);

game_tile_t *core_2048_get_tile(uint32_t x_coord, uint32_t y_coord)
{
    if (x_coord >= SCREEN_WIDTH_BLOCK_CNT || y_coord >= SCREEN_HEIGHT_BLOCK_CNT) {
        return NULL;
    }

    return &prv_game_tiles[y_coord][x_coord];
}

void core_2048_tiles_init(uint32_t first_tile_init_pos, uint32_t second_tile_init_pos)
{

    for (int x_tile_pos = 0; x_tile_pos < SCREEN_WIDTH_BLOCK_CNT; x_tile_pos++) {
        for (int y_tile_pos = 0; y_tile_pos < SCREEN_HEIGHT_BLOCK_CNT; y_tile_pos++) {


            prv_game_tiles[x_tile_pos][y_tile_pos].font_color = BLACK;
            prv_game_tiles[x_tile_pos][y_tile_pos].x_pos      = x_tile_pos;
            prv_game_tiles[x_tile_pos][y_tile_pos].y_pos      = y_tile_pos;

            if (x_tile_pos * SCREEN_WIDTH_BLOCK_CNT + y_tile_pos == first_tile_init_pos) {
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

void core_2048_check_key_pressed(KeyboardKey key_pressed)
{
    // printf("Key pressed %d \r\n", key_pressed);

    for (int key_type_idx = KEY_TYPE_UP; key_type_idx < KEY_PRESSED_TYPES_CNT; key_type_idx++) {
        for (int key_mapping_idx = 0; key_mapping_idx < MAX_KEY_MAPPINGS; key_mapping_idx++) {
            if (key_pressed == prv_keys_mapping[key_type_idx].key_mappings[key_mapping_idx]) {
                prv_key_pressed_callback(key_type_idx);
            }
        }
    }
}


static void prv_key_pressed_callback(key_pressed_types_t key_pressed_type)
{
    switch (key_pressed_type) {
    case KEY_TYPE_UP:
        // printf("KEY TYPE UP ! ");

        for (int x_tile_pos = 0; x_tile_pos < SCREEN_WIDTH_BLOCK_CNT; x_tile_pos++) {
            for (int y_tile_pos = 0; y_tile_pos < SCREEN_HEIGHT_BLOCK_CNT; y_tile_pos++) {
            }
        }
        break;

    case KEY_TYPE_DOWN:
        printf("KEY TYPE DOWN ! ");
        break;

    case KEY_TYPE_LEFT:
        printf("KEY TYPE LEFT ! ");

        // for every tile check movement possiblity

        for (int y_tile_pos = 0; y_tile_pos < SCREEN_WIDTH_BLOCK_CNT; y_tile_pos++) {
            for (int x_tile_pos = 0; x_tile_pos < SCREEN_HEIGHT_BLOCK_CNT; x_tile_pos++) {

                uint8_t tiles_to_move =
                    prv_calculate_possible_movement_tiles_cnt(x_tile_pos, y_tile_pos, KEY_TYPE_LEFT);

                prv_game_tiles[y_tile_pos][x_tile_pos].x_pos -= tiles_to_move;
            }
        }
        //
        break;

    case KEY_TYPE_RIGHT:
        printf("KEY TYPE RIGHT !");
        break;
    default:
        break;
    }
}

static uint8_t prv_calculate_possible_movement_tiles_cnt(uint8_t x_pos, uint8_t y_pos, key_pressed_types_t key_pressed)
{
    // for left movement
    uint8_t x_end_pos         = 0U;
    uint8_t tiles_to_move_cnt = 0U;

    if (x_pos > x_end_pos) {
        for (int x = x_pos; x > x_end_pos; x--) {
            if (prv_game_tiles[y_pos][x].score == 0U) {
                tiles_to_move_cnt++;
            }
        }
    }

    return tiles_to_move_cnt;
}


void core_2048_draw_grid(void)
{
    for (int i = 0; i < SCREEN_WIDTH_BLOCK_CNT; i++) {
        for (int j = 0; j < SCREEN_HEIGHT_BLOCK_CNT; j++) {
            platform_port_draw_tile(prv_game_tiles[i][j].x_pos, prv_game_tiles[i][j].y_pos,
                                    prv_game_tiles[i][j].tile_color, prv_game_tiles[i][j].score,
                                    prv_game_tiles[i][j].font_color);
        }
    }
}