#include "cub3d.h"

int key_pressed(int key, t_cub3d *cub)
{
	if (key == KEY_A)
		//A
	else if (key == KEY_S)
		//S
	else if (key == KEY_D)
		//
	else if (key == KEY_W)
		//
	else if (key == KEY_RIGHT)
		//
	else if (key == KEY_LEFT)
		//
	else if (key == KEY_ESC)
		//
	return (EXIT_SUCCESS);
}

int game_keys(t_cub3d *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, &key_pressed, cub);
	mlx_hook(cub->win, 3, 1L << 1, &key_released, cub);
	mlx_hook(cub->win, 17, 1L << 17, &exit_cross, cub);
	mlx_hook(cub->win, 6, 1L << 0, mouse, cub);

}