#include "cub3d.h"

void game_init(t_cub3d *cub)
{
	int i;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, W_WIDTH, W_HEIGHT, "Cub3DDDDD");

	// cub->img[ID_NO]->ptr = mlx_xpm_file_to_image(cub->mlx, cub->img[ID_NO]->path_tex, cub->img[ID_NO]->width, cub->img[ID_NO]->height);
	// cub->img[ID_NO]->addr = mlx_get_data_addr(cub->img[ID_NO]->ptr, cub->img[ID_NO]->bits_per_pixel, cub->img[ID_NO]->size_line, cub->img[ID_NO]->endian);
	i = 0;
	while (i < MAX)
	{
		/* code */
		cub->img[i]->ptr = mlx_xpm_file_to_image(cub->mlx, cub->img[i]->path_tex, &cub->img[i]->width, &cub->img[i]->height);
		cub->img[i]->addr = (int *)mlx_get_data_addr(cub->img[i]->ptr, &cub->img[i]->bits_p_pixel, &cub->img[i]->size_line, &cub->img[i]->endian);
		i++;
	}



}

int		game_draw_ceiling(t_cub3d *cub)
{
	int			p_w;
	int			p_h;
	double		adjust_height_half;

	adjust_height_half = ceil((double)(W_HEIGHT / 2)) - 1;
	p_h = 0;
	while (p_h < (int)adjust_height_half)
	{
		p_w = 0;
		while (p_w < W_WIDTH)
		{
			cub->img3d->addr[(int)(p_h * W_WIDTH + p_w)] = cub->color_celling;
			p_w++;
		}
		p_h++;
	}
	return (0);
}

int		game_draw_floor(t_cub3d *cub)
{
	int		p_w;
	int		p_h;
	double	adjust_height_half;

	adjust_height_half = ceil((double)(W_HEIGHT / 2)) - 1;
	p_h = (int)adjust_height_half;
	while (p_h < W_HEIGHT)
	{
		p_w = 0;
		while (p_w < W_WIDTH)
		{
			cub->img3d->addr[(int)(p_h * W_WIDTH + p_w)] = cub->color_floor;
			p_w++;
		}
		p_h++;
	}
	return (0);
}

int game_render(t_cub3d *cub)
{
	cub->img3d->ptr = mlx_new_image(cub->mlx, W_WIDTH, W_HEIGHT);
	cub->img3d->addr = (int *)mlx_get_data_addr(cub->img3d->ptr, &cub->img3d->bits_p_pixel, &cub->img3d->size_line, &cub->img3d->endian);
	game_draw_floor(cub);
	game_draw_ceiling(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img3d->ptr, 0, 0);
	return (EXIT_SUCCESS);
}

int game(t_cub3d *cub)
{
	// init parameter for player, win size, mlx
	game_init(cub);
	// mlx_do_key_autorepeatoff(cub->mlx);
	// mlx_loop_hook(cub->mlx, game_render, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
	game_key_hooks(cub);
	mlx_loop(cub->mlx);

	return (EXIT_SUCCESS);
}