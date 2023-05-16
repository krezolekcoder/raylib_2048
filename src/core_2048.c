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

static game_tile_t prv_game_tiles[TILE_CNT_ROW][TILE_CNT_ROW];

static void prv_key_pressed_callback(key_pressed_types_t key_pressed_type);

void core_2048_tiles_init(uint32_t first_tile_init_pos, uint32_t second_tile_init_pos)
{

    for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {


            prv_game_tiles[x_tile_pos][y_tile_pos].font_color = BLACK;

            if (x_tile_pos * TILE_CNT_ROW + y_tile_pos == first_tile_init_pos) {
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

game_tile_t *core_2048_get_tile(uint32_t x_coord, uint32_t y_coord)
{
    if (x_coord >= TILE_CNT_ROW || y_coord >= TILE_CNT_ROW) {
        return NULL;
    }

    return &prv_game_tiles[y_coord][x_coord];
}


static void prv_key_pressed_callback(key_pressed_types_t key_pressed_type)
{
    switch (key_pressed_type) {
    case KEY_TYPE_UP:
        for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
            for (int y_tile_pos = 1; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
                for (int y_possible_movement = y_tile_pos - 1; y_possible_movement >= 0; y_possible_movement--) {

                    if (prv_game_tiles[y_possible_movement][x_tile_pos].score == 0) {
                        prv_game_tiles[y_possible_movement][x_tile_pos].score =
                            prv_game_tiles[y_possible_movement + 1][x_tile_pos].score;
                        prv_game_tiles[y_possible_movement + 1][x_tile_pos].score = 0;
                    }
                    else if (prv_game_tiles[y_possible_movement + 1][x_tile_pos].score ==
                             prv_game_tiles[y_possible_movement][x_tile_pos].score) {
                        prv_game_tiles[y_possible_movement][x_tile_pos].score +=
                            prv_game_tiles[y_possible_movement + 1][x_tile_pos].score;
                        prv_game_tiles[y_possible_movement + 1][x_tile_pos].score = 0;
                    }
                }
            }
        }

        break;

    case KEY_TYPE_DOWN:

        for (int x_tile_pos = 0; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
            for (int y_tile_pos = 2U; y_tile_pos >= 0; y_tile_pos--) {
                for (int y_possible_movement = y_tile_pos; y_possible_movement < 3U; y_possible_movement++) {

                    if (prv_game_tiles[y_possible_movement + 1][x_tile_pos].score == 0) {
                        prv_game_tiles[y_possible_movement + 1][x_tile_pos].score =
                            prv_game_tiles[y_possible_movement][x_tile_pos].score;
                        prv_game_tiles[y_possible_movement][x_tile_pos].score = 0;
                    }
                    else if (prv_game_tiles[y_possible_movement + 1][x_tile_pos].score ==
                             prv_game_tiles[y_possible_movement][x_tile_pos].score) {
                        prv_game_tiles[y_possible_movement + 1][x_tile_pos].score +=
                            prv_game_tiles[y_possible_movement][x_tile_pos].score;
                        prv_game_tiles[y_possible_movement][x_tile_pos].score = 0;
                    }
                }
            }
        }

        break;

    case KEY_TYPE_LEFT:

        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
            for (int x_tile_pos = 1; x_tile_pos < TILE_CNT_ROW; x_tile_pos++) {
                for (int x_possible_movement = x_tile_pos - 1; x_possible_movement >= 0; x_possible_movement--) {

                    if (prv_game_tiles[y_tile_pos][x_possible_movement].score == 0) {
                        prv_game_tiles[y_tile_pos][x_possible_movement].score =
                            prv_game_tiles[y_tile_pos][x_possible_movement + 1].score;
                        prv_game_tiles[y_tile_pos][x_possible_movement + 1].score = 0;
                    }
                    else if (prv_game_tiles[y_tile_pos][x_possible_movement + 1].score ==
                             prv_game_tiles[y_tile_pos][x_possible_movement].score) {
                        prv_game_tiles[y_tile_pos][x_possible_movement].score +=
                            prv_game_tiles[y_tile_pos][x_possible_movement + 1].score;
                        prv_game_tiles[y_tile_pos][x_possible_movement + 1].score = 0;
                    }
                }
            }
        }


        break;

    case KEY_TYPE_RIGHT:

        for (int y_tile_pos = 0; y_tile_pos < TILE_CNT_ROW; y_tile_pos++) {
            for (int x_tile_pos = 2U; x_tile_pos >= 0; x_tile_pos--) {
                for (int x_possible_movement = x_tile_pos; x_possible_movement < 3U; x_possible_movement++) {

                    if (prv_game_tiles[y_tile_pos][x_possible_movement + 1].score == 0) {
                        prv_game_tiles[y_tile_pos][x_possible_movement + 1].score =
                            prv_game_tiles[y_tile_pos][x_possible_movement].score;
                        prv_game_tiles[y_tile_pos][x_possible_movement].score = 0;
                    }
                    else if (prv_game_tiles[y_tile_pos][x_possible_movement + 1].score ==
                             prv_game_tiles[y_tile_pos][x_possible_movement].score) {
                        prv_game_tiles[y_tile_pos][x_possible_movement + 1].score +=
                            prv_game_tiles[y_tile_pos][x_possible_movement].score;
                        prv_game_tiles[y_tile_pos][x_possible_movement].score = 0;
                    }
                }
            }
        }


        break;
    default:
        break;
    }
}


void core_2048_draw_grid(void)
{
    for (int i = 0; i < TILE_CNT_ROW; i++) {
        for (int j = 0; j < TILE_CNT_ROW; j++) {
            platform_port_draw_tile(prv_game_tiles[i][j].x_pos, prv_game_tiles[i][j].y_pos,
                                    prv_game_tiles[i][j].tile_color, prv_game_tiles[i][j].score,
                                    prv_game_tiles[i][j].font_color);
        }
    }
}
