#include "cub3d.h"

void game_init(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, W_WIDTH, W_HEIGHT, "Cub3D");

}

int game(t_cub3d *cub)
{
	// init parameter for player, win size, mlx
	game_init(cub);

	cub->pos.x = 10;
	cub->pos.y = 5;
	cub->rotation = 0;


	mlx_loop_hook(cub->mlx, render_frame, cub);



/* 
	mlx_hook(cub->win, 2, 1L << 0, &key_pressed, cub);
	mlx_hook(cub->win, 3, 1L << 1, &key_released, cub);
	mlx_hook(cub->win, 17, 1L << 17, &exit_cross, cub);
	mlx_hook(cub->win, 6, 1L << 0, mouse, cub);
*/
	mlx_loop(cub->mlx);


	return (EXIT_SUCCESS);
}