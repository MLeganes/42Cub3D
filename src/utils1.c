#include "cub3d.h"

// int	color_rgb(int r, int g, int b)
// {
// 	int	color;

// 	color = 0;
// 	color += r << 16;
// 	color += g << 8;
// 	color += b;
// 	return (color);
// }

int	rgb_to_colorHex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}