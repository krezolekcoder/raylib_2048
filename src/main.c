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

#include "colors_palette.h"
#include "config.h"
#include "core_2048.h"
#include "platform_port.h"
#include <../include/raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    KeyboardKey key_mappings[MAX_KEY_MAPPINGS];
} keyboard_mapping_t;

static const keyboard_mapping_t prv_keys_mapping[MOVEMENT_CNT] = {
    [MOVEMENT_UP].key_mappings    = {KEY_W,  KEY_UP,    KEY_KP_8},
    [MOVEMENT_DOWN].key_mappings  = { KEY_S, KEY_DOWN,  KEY_KP_2},
    [MOVEMENT_LEFT].key_mappings  = { KEY_A, KEY_LEFT,  KEY_KP_4},
    [MOVEMENT_RIGHT].key_mappings = { KEY_D, KEY_RIGHT, KEY_KP_6},
};

static void prv_check_key_pressed(KeyboardKey key_pressed);
static void prv_2048_game_draw_grid(void);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH + BLOCK_OFFSET, SCREEN_HEIGHT + BLOCK_OFFSET,
               "raylib [core] example - basic window");

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second


    // double input_process_time = GetTime();

    core_2048_tiles_init(2, 4);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // current_time = GetTime();
        // Update
        //----------------------------------------------------------------------------------

        prv_check_key_pressed(GetKeyPressed());
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(COLOR_EMPTY);
        prv_2048_game_draw_grid();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void prv_check_key_pressed(KeyboardKey key_pressed)
{

    for (movement_type_t movement_type = MOVEMENT_UP; movement_type < MOVEMENT_CNT; movement_type++) {
        for (int key_mapping_idx = 0; key_mapping_idx < MAX_KEY_MAPPINGS; key_mapping_idx++) {
            if (key_pressed == prv_keys_mapping[movement_type].key_mappings[key_mapping_idx]) {

                printf("MOVEMENT %d \r\n", movement_type);
                core_2048_movement_update(movement_type);
                break;
            }
        }
    }
}

void prv_2048_game_draw_grid(void)
{

    for (int y_coord = 0; y_coord < TILE_CNT_ROW; y_coord++) {
        for (int x_coord = 0; x_coord < TILE_CNT_ROW; x_coord++) {
            uint32_t tile_score = core_2048_get_tile_score(x_coord, y_coord);
            platform_port_draw_tile(x_coord, y_coord, COLOR_16, tile_score, BLACK);
        }
    }
}
