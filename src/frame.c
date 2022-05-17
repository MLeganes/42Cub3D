#include "cub3d.h"

t_cor	get_next_contact_point(t_cor pos, t_cor vec)
{
	float	mx;
	float	my;
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

void	draw_line(int column, float dist, t_cub3d *cub)
{
	int		row;
	int		wall_height;

	row = 0;
	wall_height = (W_HEIGHT / 2) / dist;
	while (row < W_HEIGHT)
	{
		if (row < W_HEIGHT / 2 - wall_height)
			cub->img3d->addr[(int)(row * (int)cub->win_w + column)] = cub->color_celling;
		else if (row > W_HEIGHT / 2 + wall_height)
			cub->img3d->addr[(int)(row * (int)cub->win_w + column)] = cub->color_floor;
		else
			cub->img3d->addr[(int)(row * (int)cub->win_w + column)] = 0;
		row++;
	}
}

int	render_frame(void *cub_ptr)
{
	int		column;
	float	multi;
	t_cub3d	*cub;
	t_cor	column_vector;
	t_cor	cam_vec;
	t_cor	pos_cntct;

	cub = (t_cub3d *)cub_ptr;
	cam_vec.x = cos(cub->rotation * 3.142857 / 180);
	cam_vec.y = sin(cub->rotation * 3.142857 / 180);
	column = 0;
	cub->img3d->ptr = mlx_new_image(cub->mlx, W_WIDTH, W_HEIGHT);
	cub->img3d->addr = (int *)mlx_get_data_addr(cub->img3d->ptr, &cub->img3d->bits_p_pixel, &cub->img3d->size_line, &cub->img3d->endian);
	while (column < W_WIDTH)
	{
		pos_cntct.x = cub->pos.x;
		pos_cntct.y = cub->pos.y;
		if (column > W_WIDTH / 2)
			multi = -((float)(W_WIDTH - 2 * column) / W_WIDTH);
		else
			multi = (float)(2 * column - W_WIDTH) / W_WIDTH;
		column_vector.x = cam_vec.x + multi * cam_vec.y;
		column_vector.y = cam_vec.y + multi * -cam_vec.x;
		while (1)
		{
			pos_cntct = get_next_contact_point(pos_cntct, column_vector);
			if ('1' == cub->map.map[(int)pos_cntct.y][(int)pos_cntct.x])
				break ;
		}
		draw_line(column, hypot(pos_cntct.x - cub->pos.x, pos_cntct.y - cub->pos.y), cub);
		column++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img3d->ptr, 0, 0);	
	return (0);
}
