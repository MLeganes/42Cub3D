#include "cub3d.h"

int key_pressed(int key, t_cub3d *cub)
{
	(void)key;
	(void)cub;

	// double	movestep;
	// double	next_playerx;
	// double	next_playery;
	// double	move_angle;

	// if (key == KEY_A)
	// 	//move_angle = normalrad
	// else if (key == KEY_S)
	// 	//S
	// else if (key == KEY_D)
	// 	//
	// else if (key == KEY_W)
	// 	//
	// else if (key == KEY_RIGHT)
	// 	//
	// else if (key == KEY_LEFT)
	// 	//
	// else if (key == KEY_ESC)
		//
	return (EXIT_SUCCESS);
}

int key_esc(int key, t_cub3d *cub)
{
	(void)key;
	(void)cub;
	//free everything
	exit(EXIT_SUCCESS);
}



int game_key_hooks(t_cub3d *cub)
{
	mlx_do_key_autorepeatoff(cub->mlx);
	mlx_hook(cub->win, 2, 1L << 2, &key_pressed, cub);
	// mlx_hook(cub->win, 3, 1L << 1, &key_released, cub);
	mlx_hook(cub->win, 17, 1L << 17, &key_esc, cub);
	// mlx_hook(cub->win, 6, 1L << 0, mouse_hook, cub);
	return (EXIT_SUCCESS);
}