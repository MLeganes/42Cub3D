/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:48:25 by amorcill          #+#    #+#             */
/*   Updated: 2022/05/19 16:49:04 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_cub3d_img(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < MAX)
	{
		if (cub->img[i])
		{
			if (cub->img[i]->path_tex)
			{
				mlx_destroy_image(cub->mlx, cub->img[i]->ptr);
				free(cub->img[i]->path_tex);
			}
			free(cub->img[i]);
		}
		i++;
	}
	return ;
}

static void	free_cub3d_map(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.nolines)
	{
		if (cub->map.map[i])
			free(cub->map.map[i]);
		i++;
	}
	if (cub->map.map)
		free(cub->map.map);
	mlx_destroy_window(cub->mlx, cub->win);
	return ;
}

int	free_game(t_cub3d *cub)
{
	free_cub3d_img(cub);
	free_cub3d_map(cub);
	exit (EXIT_SUCCESS);
}

int	exit_game(t_cub3d *cub)
{
	free_game(cub);
	return (EXIT_FAILURE);
}

int exit_game_2(void *cub)
{
	free_game((t_cub3d *)cub);
	return (EXIT_FAILURE);
}
