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


	mlx_loop_hook(cub->mlx, render_frame, cub);

	game_keys(cub);

/* 
	
*/
	mlx_loop(cub->mlx);


	return (EXIT_SUCCESS);
}