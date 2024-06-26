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
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  KeyboardKey key_mappings[MAX_KEY_MAPPINGS];
} keyboard_mapping_t;

static void prv_check_key_pressed(KeyboardKey key_pressed);
static void prv_2048_game_draw_grid(void);

static const keyboard_mapping_t prv_keys_mapping[MOVEMENT_CNT] = {
    [MOVEMENT_UP].key_mappings = {KEY_W, KEY_UP, KEY_KP_8},
    [MOVEMENT_DOWN].key_mappings = {KEY_S, KEY_DOWN, KEY_KP_2},
    [MOVEMENT_LEFT].key_mappings = {KEY_A, KEY_LEFT, KEY_KP_4},
    [MOVEMENT_RIGHT].key_mappings = {KEY_D, KEY_RIGHT, KEY_KP_6},
};

const Color prv_tile_colors_lut[11U] = {
    COLOR_EMPTY, COLOR_2,   COLOR_4,   COLOR_8,   COLOR_16,   COLOR_32,
    COLOR_64,    COLOR_128, COLOR_256, COLOR_512, COLOR_1024, COLOR_2048};

#define FRAME_TIME (0.01667)
#define FRAMES_PER_MOVEMENT (2)
#define MOVEMENT_LENGTH (20)

void get_next_pos_animation(uint32_t *current_x_pos, uint32_t destination_x_pos,
                            double current_time, double *timer) {
  if ((current_time - *timer) >= (FRAMES_PER_MOVEMENT * FRAME_TIME)) {

    *timer = current_time;
    if (*current_x_pos >= destination_x_pos) {
      *current_x_pos = destination_x_pos;
    } else {
      *current_x_pos += MOVEMENT_LENGTH;
    }
  }
}

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------

  InitWindow(SCREEN_WIDTH + BLOCK_OFFSET, SCREEN_HEIGHT + BLOCK_OFFSET,
             "raylib [core] example - basic window");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  double timer = GetTime();

  core_2048_set_tile_score(0, 2, 4);
  core_2048_set_tile_score(3, 1, 2);
  //--------------------------------------------------------------------------------------
  // Main game loop

  uint32_t pos_counter = 0;

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    double current_time = GetTime();
    // Update
    //----------------------------------------------------------------------------------

    prv_check_key_pressed(GetKeyPressed());
    //----------------------------------------------------------------------------------

    // Draw
    //-------
    //---------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(COLOR_EMPTY);
    prv_2048_game_draw_grid();

    get_next_pos_animation(&pos_counter, 2 * BLOCK_SIZE, current_time, &timer);

    uint32_t score = 1024U;
    uint32_t color_idx = log2(score);
    platform_port_draw_tile_pixel(pos_counter, 0,
                                  prv_tile_colors_lut[color_idx], score, BLACK);

    // platform_port_draw_tile(0, 0, prv_tile_colors_lut[color_idx], score,
    // BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

void prv_check_key_pressed(KeyboardKey key_pressed) {

  for (movement_type_t movement_type = MOVEMENT_UP;
       movement_type < MOVEMENT_CNT; movement_type++) {
    for (int key_mapping_idx = 0; key_mapping_idx < MAX_KEY_MAPPINGS;
         key_mapping_idx++) {
      if (key_pressed ==
          prv_keys_mapping[movement_type].key_mappings[key_mapping_idx]) {

        printf("MOVEMENT %d \r\n", movement_type);
        core_2048_movement_update(movement_type);

        uint32_t x_coord = 0U;
        uint32_t y_coord = 0U;

        core_2048_get_random_free_tile_coords(&x_coord, &y_coord);
        core_2048_set_tile_score(x_coord, y_coord, 2U);

        break;
      }
    }
  }
}

void prv_2048_game_draw_grid(void) {

  for (int y_coord = 0; y_coord < TILE_CNT_ROW; y_coord++) {
    for (int x_coord = 0; x_coord < TILE_CNT_ROW; x_coord++) {
      uint32_t tile_score = core_2048_get_tile_score(x_coord, y_coord);

      uint32_t color_idx = log2(tile_score);
      platform_port_draw_tile(x_coord, y_coord, prv_tile_colors_lut[color_idx],
                              tile_score, BLACK);
    }
  }
}
