/**
 * @file main.c
 * @author krezolekcoder (https://github.com/krezolekcoder)
 * @brief
 * @version 0.1
 * @date 2022-08-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <../include/raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "colors_pallete.h"

#define MAX_KEY_MAPPINGS (3U)
#define KEYS_CNT         (4U)

#define BLOCK_SIZE              (125U)
#define BLOCK_OFFSET            (18U)
#define SCREEN_WIDTH_BLOCK_CNT  (4U)
#define SCREEN_HEIGHT_BLOCK_CNT (4U)
#define SCREEN_WIDTH            (BLOCK_SIZE * SCREEN_WIDTH_BLOCK_CNT)
#define SCREEN_HEIGHT           (BLOCK_SIZE * SCREEN_HEIGHT_BLOCK_CNT)
#define FONT_SIZE               (32U)
#define TEXT_IN_BLOCK_OFFSET    (5U)

#define TEXT_IN_BLOCK_PIXEL_VALUE(box_start_x_coord)                                               \
    ((box_start_x_coord) + BLOCK_OFFSET + TEXT_IN_BLOCK_OFFSET)

typedef enum {
    KEY_TYPE_UP = 0,
    KEY_TYPE_DOWN,
    KEY_TYPE_LEFT,
    KEY_TYPE_RIGHT,
    KEY_PRESSED_TYPES_CNT,
} key_pressed_types_t;

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


static const keyboard_mapping_t prv_keys_mapping[KEY_PRESSED_TYPES_CNT] = {
    [KEY_TYPE_UP].key_mappings    = {KEY_W,  KEY_UP,    KEY_KP_8},
    [KEY_TYPE_DOWN].key_mappings  = { KEY_S, KEY_DOWN,  KEY_KP_2},
    [KEY_TYPE_LEFT].key_mappings  = { KEY_A, KEY_LEFT,  KEY_KP_4},
    [KEY_TYPE_RIGHT].key_mappings = { KEY_D, KEY_RIGHT, KEY_KP_6},
};

static game_tile_t prv_game_tiles[SCREEN_WIDTH_BLOCK_CNT][SCREEN_HEIGHT_BLOCK_CNT];

void prv_grid_draw(void);
void tiles_init(void);
void platform_port_draw_tile(uint32_t x_pos, uint32_t y_pos, Color color, uint32_t score, Color font_color);

void check_key_pressed(KeyboardKey key_pressed);
void key_pressed_callback(key_pressed_types_t key_pressed_type);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    double current_time = GetTime();

    InitWindow(SCREEN_WIDTH + BLOCK_OFFSET, SCREEN_HEIGHT + BLOCK_OFFSET,
               "raylib [core] example - basic window");

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    tiles_init();

    double input_process_time = GetTime();


    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        current_time = GetTime();
        // Update
        //----------------------------------------------------------------------------------

        check_key_pressed(GetKeyPressed());
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(COLOR_EMPTY);
        prv_grid_draw();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void prv_grid_draw(void)
{
    for (int i = 0; i < SCREEN_WIDTH_BLOCK_CNT; i++) {
        for (int j = 0; j < SCREEN_HEIGHT_BLOCK_CNT; j++) {
            platform_port_draw_tile(prv_game_tiles[i][j].x_pos, prv_game_tiles[i][j].y_pos,
                                    prv_game_tiles[i][j].tile_color, prv_game_tiles[i][j].score,
                                    prv_game_tiles[i][j].font_color);
        }
    }
}

void tiles_init(void)
{
    double current_time = GetTime();
    srand(current_time);

    uint32_t first_visible_tile_idx  = rand() % 16U;
    uint32_t second_visible_tile_idx = rand() % 16U;

    for (int x_tile_pos = 0; x_tile_pos < SCREEN_WIDTH_BLOCK_CNT; x_tile_pos++) {
        for (int y_tile_pos = 0; y_tile_pos < SCREEN_HEIGHT_BLOCK_CNT; y_tile_pos++) {


            prv_game_tiles[x_tile_pos][y_tile_pos].font_color = BLACK;
            prv_game_tiles[x_tile_pos][y_tile_pos].x_pos      = x_tile_pos;
            prv_game_tiles[x_tile_pos][y_tile_pos].y_pos      = y_tile_pos;

            if (x_tile_pos * SCREEN_WIDTH_BLOCK_CNT + y_tile_pos == first_visible_tile_idx) {
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

void check_key_pressed(KeyboardKey key_pressed)
{
    // printf("Key pressed %d \r\n", key_pressed);

    for (int key_type_idx = KEY_TYPE_UP; key_type_idx < KEY_PRESSED_TYPES_CNT; key_type_idx++) {
        for (int key_mapping_idx = 0; key_mapping_idx < MAX_KEY_MAPPINGS; key_mapping_idx++) {
            if (key_pressed == prv_keys_mapping[key_type_idx].key_mappings[key_mapping_idx]) {
                key_pressed_callback(key_type_idx);
            }
        }
    }
}


void key_pressed_callback(key_pressed_types_t key_pressed_type)
{
    switch (key_pressed_type) {
    case KEY_TYPE_UP:
        // printf("KEY TYPE UP ! ");

        for (int x_tile_pos = 0; x_tile_pos < SCREEN_WIDTH_BLOCK_CNT; x_tile_pos++) {
            for (int y_tile_pos = 0; y_tile_pos < SCREEN_HEIGHT_BLOCK_CNT; y_tile_pos++) {

                if (prv_game_tiles[x_tile_pos][y_tile_pos].score == 0U) {
                    continue;
                }

                // Get tile count for given movement
                prv_game_tiles[x_tile_pos][y_tile_pos].font_color = BLACK;
                prv_game_tiles[x_tile_pos][y_tile_pos].x_pos      = x_tile_pos;
                prv_game_tiles[x_tile_pos][y_tile_pos].y_pos      = y_tile_pos;
            }
        }
        break;

    case KEY_TYPE_DOWN:
        printf("KEY TYPE DOWN ! ");
        break;

    case KEY_TYPE_LEFT:
        printf("KEY TYPE LEFT ! ");
        break;

    case KEY_TYPE_RIGHT:
        printf("KEY TYPE RIGHT !");
        break;
    default:
        break;
    }
}


void platform_port_draw_tile(uint32_t x_pos, uint32_t y_pos, Color color, uint32_t score, Color font_color)
{
    char score_buf[10U];
    sprintf(score_buf, "%d", score);
    DrawRectangle(x_pos * BLOCK_SIZE + BLOCK_OFFSET, y_pos * BLOCK_SIZE + BLOCK_OFFSET,
                  BLOCK_SIZE - BLOCK_OFFSET, BLOCK_SIZE - BLOCK_OFFSET, color);

    DrawText(score_buf, TEXT_IN_BLOCK_PIXEL_VALUE(x_pos * BLOCK_SIZE),
             y_pos * BLOCK_SIZE + BLOCK_OFFSET + FONT_SIZE, FONT_SIZE, font_color);
}
