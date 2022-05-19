/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnies <mnies@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:44:03 by mnies             #+#    #+#             */
/*   Updated: 2022/05/19 15:51:30 by mnies            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	frame_draw_pixel_wall(int column, int row, int height, t_draw *draw)
{
	int	h;
	int	id;
	int	pos;

	if (draw->poscntct->x - (int)draw->poscntct->x == 0
		&& draw->poscntct->x > draw->cub->pos.x)
		id = ID_NO;
	else if (draw->poscntct->x - (int)draw->poscntct->x == 0)
		id = ID_SO;
	else if (draw->poscntct->y > draw->cub->pos.y)
		id = ID_WE;
	else
		id = ID_EA;
	h = row - ((W_HEIGHT - height) / 2);
	if (draw->poscntct->x - (int)draw->poscntct->x == 0)
		pos = (draw->poscntct->y - (int)draw->poscntct->y)
			* draw->cub->img[id]->width - 1;
	else
		pos = (draw->poscntct->x - (int)draw->poscntct->x)
			* draw->cub->img[id]->width - 1;
	pos = (float)h / height * (draw->cub->img[id]->height - 1)
		+ pos * (draw->cub->img[id]->height - 1);
	draw->cub->img3d->addr[(int)(row * (int)draw->cub->win_w + column)]
		= draw->cub->img[id]->addr[pos];
}

void	frame_draw_line(int column, t_cor *poscntct, t_cub3d *cub)
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
		if (row < (W_HEIGHT - wall_height) / 2)
			cub->img3d->addr[(int)(row * (int)cub->win_w + column)]
				= cub->color_celling;
		else if (row > W_HEIGHT - (W_HEIGHT - wall_height) / 2)
			cub->img3d->addr[(int)(row * (int)cub->win_w + column)]
				= cub->color_floor;
		else
			frame_draw_pixel_wall(column, row, wall_height, &draw);
		row++;
	}
}

void	frame_render_loop(t_cor *cam_vec, t_cub3d *cub)
{
	int		column;
	float	multi;
	t_cor	column_vector;
	t_cor	pos_cntct;

	column = 0;
	while (column < W_WIDTH)
	{
		pos_cntct.x = cub->pos.x;
		pos_cntct.y = cub->pos.y;
		if (column > W_WIDTH / 2)
			multi = -((float)(W_WIDTH - 2 * column) / W_WIDTH);
		else
			multi = (float)(2 * column - W_WIDTH) / W_WIDTH;
		column_vector.x = cam_vec->x + multi * cam_vec->y;
		column_vector.y = cam_vec->y + multi * -cam_vec->x;
		while (!contact_is_wall(cub, &pos_cntct, &column_vector))
			contact_get_next(&pos_cntct, &column_vector);
		frame_draw_line(column, &pos_cntct, cub);
		column++;
	}
}

int	render_frame(void *cub_ptr)
{
	t_cub3d	*cub;
	t_cor	cam_vec;

	cub = (t_cub3d *)cub_ptr;
	cam_vec.x = cos(cub->rotation * 3.142857 / 180);
	cam_vec.y = sin(cub->rotation * 3.142857 / 180);
	cub->img3d->ptr = mlx_new_image(cub->mlx, W_WIDTH, W_HEIGHT);
	cub->img3d->addr = (int *)mlx_get_data_addr(cub->img3d->ptr,
			&cub->img3d->bits_p_pixel, &cub->img3d->size_line,
			&cub->img3d->endian);
	frame_render_loop(&cam_vec, cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img3d->ptr, 0, 0);
	return (0);
}
