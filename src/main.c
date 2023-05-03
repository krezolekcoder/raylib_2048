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

#define BLOCK_SIZE              (120U)
#define SCREEN_WIDTH_BLOCK_CNT  (4U)
#define SCREEN_HEIGHT_BLOCK_CNT (4U)
#define SCREEN_WIDTH            (BLOCK_SIZE * SCREEN_WIDTH_BLOCK_CNT)
#define SCREEN_HEIGHT           (BLOCK_SIZE * SCREEN_HEIGHT_BLOCK_CNT)

static void prv_grid_draw(void);


void tiles_init(void);
void platform_port_draw_tile(uint32_t x_pos, uint32_t y_pos, Color color, uint32_t score);

typedef struct {
    uint32_t score;
    uint32_t x_pos;
    uint32_t y_pos;
    Color    color;
} game_tile_t;

static game_tile_t prv_game_tiles[SCREEN_WIDTH_BLOCK_CNT][SCREEN_HEIGHT_BLOCK_CNT];

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    double current_time = GetTime();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
    srand(current_time);

    tiles_init();

    double input_process_time = GetTime();


    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        current_time = GetTime();
        // Update
        //----------------------------------------------------------------------------------
        KeyboardKey key_pressed = GetKeyPressed();


        if (key_pressed) {
            printf("Hello world ! %d \r\n", key_pressed);
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


        ClearBackground(BLACK);
        DrawRectangle(1 * BLOCK_SIZE, 1 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, YELLOW);
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


static void prv_grid_draw(void)
{
    for (int i = 0; i < SCREEN_WIDTH_BLOCK_CNT; i++) {
        for (int j = 0; j < SCREEN_HEIGHT_BLOCK_CNT; j++) {
            platform_port_draw_tile(prv_game_tiles[i][j].x_pos, prv_game_tiles[i][j].y_pos,
                                    prv_game_tiles[i][j].color, prv_game_tiles[i][j].score);
        }
    }
}

void tiles_init(void)
{
    for (int x_tile_pos = 0; x_tile_pos < SCREEN_WIDTH_BLOCK_CNT; x_tile_pos++) {
        for (int y_tile_pos = 0; y_tile_pos < SCREEN_HEIGHT_BLOCK_CNT; y_tile_pos++) {

            prv_game_tiles[x_tile_pos][y_tile_pos].color = YELLOW;
            prv_game_tiles[x_tile_pos][y_tile_pos].score = x_tile_pos * 2U;
            prv_game_tiles[x_tile_pos][y_tile_pos].x_pos = x_tile_pos;
            prv_game_tiles[x_tile_pos][y_tile_pos].y_pos = y_tile_pos;

            printf("%d %d %d \r\n", x_tile_pos, y_tile_pos, prv_game_tiles[x_tile_pos][y_tile_pos].score);
        }
    }
}
void platform_port_draw_tile(uint32_t x_pos, uint32_t y_pos, Color color, uint32_t score)
{
    char score_buf[10U];
    sprintf(score_buf, "%d", score);
    DrawRectangle(x_pos * BLOCK_SIZE, y_pos * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, color);
    DrawText(score_buf, (x_pos * BLOCK_SIZE) + (BLOCK_SIZE / 2) - 20U,
             (y_pos * BLOCK_SIZE) + (BLOCK_SIZE / 2) - 20U, 40U, WHITE);
}
