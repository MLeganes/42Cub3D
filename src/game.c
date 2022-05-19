/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:46:04 by amorcill          #+#    #+#             */
/*   Updated: 2022/05/19 16:47:39 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_init(t_cub3d *cub)
{
	int	i;

	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	i = 0;
	while (i < MAX)
	{
		cub->img[i]->ptr = mlx_xpm_file_to_image(cub->mlx,
				cub->img[i]->path_tex, &cub->img[i]->width,
				&cub->img[i]->height);
		cub->img[i]->addr = (int *)mlx_get_data_addr(cub->img[i]->ptr,
				&cub->img[i]->bits_p_pixel, &cub->img[i]->size_line,
				&cub->img[i]->endian);
		i++;
	}
}

int	game(t_cub3d *cub)
{
	game_init(cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
	game_key_hooks(cub);
	mlx_loop(cub->mlx);
	return (EXIT_SUCCESS);
}
