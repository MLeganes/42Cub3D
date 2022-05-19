/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnies <mnies@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:23 by mnies             #+#    #+#             */
/*   Updated: 2022/05/19 15:42:24 by mnies            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	contact_do_step(float *pos, float *vec)
{
	if (*vec < 0 && (int)(*pos) - (*pos) == 0)
		return ((int)(*pos) - 1);
	if (*vec > 0)
		return ((int)(*pos) + 1);
	else
		return ((int)(*pos));
}

void	contact_get_next(t_cor *pos, t_cor *vec)
{
	float	mx;
	float	my;

	mx = INT32_MAX;
	if (vec->x < 0 && pos->x - (int)pos->x == 0)
		mx = 1 / -vec->x;
	else if (vec->x > 0)
		mx = (1 - (pos->x - (int)pos->x)) / vec->x;
	else if (vec->x < 0)
		mx = (pos->x - (int)pos->x) / -vec->x;
	my = INT32_MAX;
	if (vec->y < 0 && pos->y - (int)pos->y == 0)
		my = 1 / -vec->y;
	else if (vec->y > 0)
		my = (1 - (pos->y - (int)pos->y)) / vec->y;
	else if (vec->y < 0)
		my = (pos->y - (int)pos->y) / -vec->y;
	if (vec->x == 0 || my < mx)
		pos->x = pos->x + vec->x * my;
	else
		pos->x = contact_do_step(&(pos->x), &(vec->x));
	if (vec->y == 0 || my > mx)
		pos->y = pos->y + vec->y * mx;
	else
		pos->y = contact_do_step(&(pos->y), &(vec->y));
}

int	contact_is_wall(t_cub3d *cub, t_cor *pos_cntct, t_cor *vec)
{
	if (vec->y < 0 && (int)pos_cntct->y - pos_cntct->y == 0
		&& '1' == cub->map.map[(int)pos_cntct->y - 1][(int)pos_cntct->x])
		return (1);
	else if (vec->x < 0 && (int)pos_cntct->x - pos_cntct->x == 0
		&& '1' == cub->map.map[(int)pos_cntct->y][(int)pos_cntct->x - 1])
		return (1);
	else if ('1' == cub->map.map[(int)pos_cntct->y][(int)pos_cntct->x])
		return (1);
	return (0);
}
