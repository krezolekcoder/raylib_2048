#include "platform_port.h"
#include "config.h"


#define TEXT_IN_BLOCK_PIXEL_VALUE(box_start_x_coord)                                               \
    ((box_start_x_coord) + BLOCK_OFFSET + TEXT_IN_BLOCK_OFFSET)


void platform_port_draw_tile(uint32_t x_pos, uint32_t y_pos, Color color, uint32_t score, Color font_color)
{
    char score_buf[10U];
    sprintf(score_buf, "%d", score);
    DrawRectangle(x_pos * BLOCK_SIZE + BLOCK_OFFSET, y_pos * BLOCK_SIZE + BLOCK_OFFSET,
                  BLOCK_SIZE - BLOCK_OFFSET, BLOCK_SIZE - BLOCK_OFFSET, color);

    DrawText(score_buf, TEXT_IN_BLOCK_PIXEL_VALUE(x_pos * BLOCK_SIZE),
             y_pos * BLOCK_SIZE + BLOCK_OFFSET + FONT_SIZE, FONT_SIZE, font_color);
}
