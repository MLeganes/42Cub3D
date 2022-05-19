#include "cub3d.h"

void	player_move(t_cub3d *cub, int move)
{
	t_cor	move_vec;
	t_cor	pos_cntct;

	pos_cntct.x = cub->pos.x;
	pos_cntct.y = cub->pos.y;
	printf("key pressed %d\n", move);
	move_vec.x = 0.1 * cos((cub->rotation + move) * 3.142857 / 180);
	move_vec.y = 0.1 * sin((cub->rotation + move) * 3.142857 / 180);
	while (!contact_is_wall(cub, &pos_cntct, &move_vec))
		contact_get_next(&pos_cntct, &move_vec);
	if ((cub->pos.x < pos_cntct.x && cub->pos.x + move_vec.x < pos_cntct.x)
		|| (cub->pos.x > pos_cntct.x && cub->pos.x + move_vec.x > pos_cntct.x))
		cub->pos.x = cub->pos.x + move_vec.x;
	if ((cub->pos.y < pos_cntct.y && cub->pos.y + move_vec.y < pos_cntct.y)
		|| (cub->pos.y > pos_cntct.y && cub->pos.y + move_vec.y > pos_cntct.y))
		cub->pos.y = cub->pos.y + move_vec.y;
}

// static int key_esc(int key, t_cub3d *cub)
// {
// 	(void)key;
// 	free_game(cub);
// 	return (EXIT_FAILURE);
// }

int key_pressed(int key, t_cub3d *cub)
{
	if (key == KEY_A)
		player_move(cub, 90);
	else if (key == KEY_S)
		player_move(cub, 180);
	else if (key == KEY_D)
		player_move(cub, 270);
	else if (key == KEY_W)
		player_move(cub, 0);
	if (key == KEY_RIGHT)
		cub->rotation = cub->rotation - 6;
	else if (key == KEY_LEFT)
		cub->rotation = cub->rotation + 6;
	else if (key == KEY_ESC)
		exit_game(key, cub);
	return (EXIT_SUCCESS);
}

int game_key_hooks(t_cub3d *cub)
{
	mlx_hook(cub->win, 2, 1L << 2, &key_pressed, cub);
	mlx_hook(cub->win, 17, 1L << 17, &exit_game, &cub);
	return (EXIT_SUCCESS);
}
