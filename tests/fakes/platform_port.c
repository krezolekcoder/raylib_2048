#include "platform_port.h"
#include <stdlib.h>
#include <time.h>

void platform_port_draw_tile(uint32_t x_pos, uint32_t y_pos, Color color, uint32_t score, Color font_color)
{
}

uint32_t platform_port_get_random_nbr(uint32_t lower, uint32_t upper)
{
    srand(time(0));
    return (rand() % (upper - lower + 1)) + lower;
}