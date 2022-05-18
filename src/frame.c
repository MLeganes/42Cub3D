#include "cub3d.h"

float	step(float *pos, float *vec)
{
	if (*vec < 0 && (int)(*pos) - (*pos) == 0)
		return ((int)(*pos) - 1);
	if (*vec > 0)
		return ((int)(*pos) + 1);
	else
		return ((int)(*pos));
}

void	get_next_contact_point(t_cor *pos, t_cor *vec)
{
	float	mx;
	float	my;

	if (vec->x < 0 && pos->x - (int)pos->x == 0)
		mx = 1 / -vec->x;
	else if (vec->x > 0)
		mx = (1 - (pos->x - (int)pos->x)) / vec->x;
	else if (vec->x < 0)
		mx = (pos->x - (int)pos->x) / -vec->x;
	else
		mx = INT32_MAX;
	if (vec->y < 0 && pos->y - (int)pos->y == 0)
		my = 1 / -vec->y;
	else if (vec->y > 0)
		my = (1 - (pos->y - (int)pos->y)) / vec->y;
	else if (vec->y < 0)
		my = (pos->y - (int)pos->y) / -vec->y;
	else
		my = INT32_MAX;
	if (vec->x == 0 || my < mx)
		pos->x = pos->x + vec->x * my;
	else
		pos->x = step(&(pos->x), &(vec->x));
	if (vec->y == 0 || my > mx)
		pos->y = pos->y + vec->y * mx;
	else
		pos->y = step(&(pos->y), &(vec->y));
	//return (pos);
}


void	draw_pixel_wall(int column, int row, float height, t_draw *draw)
{
	int	h;

	h = row - ((W_HEIGHT - height) / 2);
	if (draw->poscntct->x - (int)draw->poscntct->x == 0
		&& draw->poscntct->y - (int)draw->poscntct->y < 0.01)
		draw->cub->img3d->addr[(int)(row * (int)draw->cub->win_w + column)] = 0;
	else if (draw->poscntct->y - (int)draw->poscntct->y == 0
		&& draw->poscntct->x - (int)draw->poscntct->x < 0.01)
		draw->cub->img3d->addr[(int)(row * (int)draw->cub->win_w + column)] = 123124;
	else
		draw->cub->img3d->addr[(int)(row * (int)draw->cub->win_w + column)] = 244;
}

void	draw_line(int column, t_cor *poscntct, t_cub3d *cub)
{
	int		row;
	int		wall_height;
	t_draw	draw;
	float	dist;

	dist = hypot(poscntct->x - cub->pos.x, poscntct->y - cub->pos.y);
	draw.cub = cub;
	draw.poscntct = poscntct;
	row = 0;
	wall_height = (W_HEIGHT / 2) / dist;
	while (row < W_HEIGHT)
	{
		if (row < W_HEIGHT / 2 - wall_height)
			cub->img3d->addr[(int)(row * (int)cub->win_w + column)] = cub->color_celling;
		else if (row > W_HEIGHT / 2 + wall_height)
			cub->img3d->addr[(int)(row * (int)cub->win_w + column)] = cub->color_floor;
		else
			draw_pixel_wall(column, row, wall_height, &draw);
		row++;
	}
}

int	is_wall(t_cub3d *cub, t_cor *pos_cntct, t_cor *column_vector)
{
	(void)column_vector;
	if (cub->pos.y > pos_cntct->y && (int)pos_cntct->y - pos_cntct->y == 0
		&& '1' == cub->map.map[(int)pos_cntct->y - 1][(int)pos_cntct->x])
		return (1);
	else if (cub->pos.x > pos_cntct->x && (int)pos_cntct->x - pos_cntct->x == 0
		&& '1' == cub->map.map[(int)pos_cntct->y][(int)pos_cntct->x - 1])
		return (1);
	else if ('1' == cub->map.map[(int)pos_cntct->y][(int)pos_cntct->x])
		return (1);
	return (0);
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

		while (!is_wall(cub, &pos_cntct, &column_vector))
			get_next_contact_point(&pos_cntct, &column_vector);
		draw_line(column, &pos_cntct, cub);
		column++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img3d->ptr, 0, 0);
	return (0);
}
