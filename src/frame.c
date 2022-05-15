#include "cub3d.h"

t_cor	get_next_contact_point(t_cor pos, t_cor vec);

void	draw_line(int column, int height, double dist, t_cub3d *cub, void *mlx, void *win)
{
	int		row;
	int		wall_height;

	(void)cub;
	row = 0;
	wall_height = (height / 2) / dist;
	while (row <= height)
	{
		if (row < height / 2 - wall_height)
			mlx_pixel_put(mlx, win, column, row, cub->color_celling);
		else if (row > height / 2 + wall_height)
			mlx_pixel_put(mlx, win, column, row, cub->color_floor);
		row++;
	}
}

void	draw_frame(int width, int height, int deg, t_cor pos, t_cub3d *cub, void *mlx, void *win)
{
	int		column;
	double	multi;
	t_cor	column_vector;
	t_cor	cam_vec;
	t_cor	pos_cntct;

	cam_vec.x = cos(deg * 3.142857 / 180);
	cam_vec.y = sin(deg * 3.142857 / 180);
	column = 0;
	while (column <= width)
	{
		pos_cntct.x = pos.x;
		pos_cntct.y = pos.y;
		if (column > width / 2)
			multi = -((double)(width - 2 * column) / width);
		else
			multi = (double)(2 * column - width) / width;
		column_vector.x = cam_vec.x + multi * cam_vec.y;
		column_vector.y = cam_vec.y + multi * -cam_vec.x;
		while (1)
		{
			pos_cntct = get_next_contact_point(pos_cntct, column_vector);
			if ('1' == cub->map.map[(int)pos_cntct.y][(int)pos_cntct.x])
				break ;
		}
		draw_line(column, height, hypot(pos_cntct.x - pos.x, pos_cntct.y - pos.y), cub, mlx, win);
		column++;
	}
}

void	test_frame(t_cub3d *cub)
{
	void	*win;
	void	*mlx;
	t_cor	pos;
	int		width;
	int		height;

	pos.x = 15;
	pos.y = 1.5;
	height = 500;
	width = 1000;
	cub->color_celling = 255;
	cub->color_floor = 45345;
	// while (1)
	// {
	// 	pos = get_next_contact_point(pos, vec);
	// 	if ('1' == cub->map.map[(int)pos.y][(int)pos.x])
	// 		break ;
	// }
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "test");
	draw_frame(width, height, 360, pos, cub, mlx, win);
	// mlx_pixel_put(mlx, win, 10, 10, 242);
	mlx_loop(mlx);
}

t_cor	get_next_contact_point(t_cor pos, t_cor vec)
{
	double	mx;
	double	my;
	int		stepx;
	int		stepy;

	stepx = 1;
	if (vec.x < 0)
		stepx = -1;
	stepy = 1;
	if (vec.y < 0)
		stepy = -1;
	if (vec.y != 0 && vec.x != 0)
	{
		my = (stepy - (pos.y - (long)pos.y)) / vec.y;
		mx = (stepx - (pos.x - (long)pos.x)) / vec.x;
	}
	if (vec.y != 0 && vec.x != 0 && my > mx)
		pos.y = pos.y + vec.y * mx;
	else if (vec.y != 0)
		pos.y = (long)(pos.y + stepy);
	if (vec.x != 0 && vec.y != 0 && my < mx)
		pos.x = pos.x + vec.x * my;
	else if (vec.x != 0)
		pos.x = (long)(pos.x + stepx);
	return (pos);
}
