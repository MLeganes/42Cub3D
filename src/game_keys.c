#include "cub3d.h"

void player_move(t_cub3d *cub, int move)
{
	t_cor move_vec;
	t_cor pos_cntct;

	pos_cntct.x = cub->pos.x;
	pos_cntct.y = cub->pos.y;
	printf("key pressed %d\n", move);
	move_vec.x = 0.1 * cos((cub->rotation + move) * 3.142857 / 180);
	move_vec.y = 0.1 * sin((cub->rotation + move) * 3.142857 / 180);

	get_next_contact_point(&pos_cntct, &move_vec);
	
	//1.check point inside the block
	//if (cub->map.map[(int)pos_cntct.y][(int)pos_cntct.x] == '1')
		//walll - no move
	
	//2.
	//
	cub->pos.x = cub->pos.x + move_vec.x;
	cub->pos.y = cub->pos.y + move_vec.y;

}

int key_pressed(int key, t_cub3d *cub)
{
	(void)key;
	(void)cub;

	// double	movestep;
	// double	next_playerx;
	// double	next_playery;
	// double	move_angle;

	if (key == KEY_A)
		player_move(cub, 90);
	else if (key == KEY_S)
		player_move(cub, 180);
	else if (key == KEY_D)
		player_move(cub, 270);
	else if (key == KEY_W)
		player_move(cub, 0);
	if (key == KEY_RIGHT)
		cub->rotation = cub->rotation - 6; //check if its 360 to 0
	else if (key == KEY_LEFT)
		cub->rotation = cub->rotation + 6;
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