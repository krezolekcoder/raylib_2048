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
#include <../include/raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    double current_time = GetTime();

    InitWindow(SCREEN_WIDTH + BLOCK_OFFSET, SCREEN_HEIGHT + BLOCK_OFFSET,
               "raylib [core] example - basic window");

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second


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
