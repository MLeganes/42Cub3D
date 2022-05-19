/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:10:40 by mnies             #+#    #+#             */
/*   Updated: 2022/05/19 18:07:34 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_count_lines(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	map_max_strlen(char **strs)
{
	int		i;
	int		j;
	int		max_len;

	i = 0;
	j = 0;
	max_len = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
			j++;
		if (j > max_len)
			max_len = j;
		i++;
	}
	return (max_len);
}

double	calculate_tilesize(t_cub3d *cub)
{
	int	map_resratio_x;
	int	map_resratio_y;

	map_resratio_x = (int)((cub->win_w / cub->map.cols) / 3);
	map_resratio_y = (int)((cub->win_h / cub->map.rows) / 3);
	if (map_resratio_x < map_resratio_y)
		return ((double)(map_resratio_x));
	else
		return ((double)(map_resratio_y));
}
