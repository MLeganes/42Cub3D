/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:28:28 by amorcill          #+#    #+#             */
/*   Updated: 2022/05/01 21:22:06 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cub3d_init(t_cub3d *cub)
{
	cub->img_ea = NULL;
	cub->img[ID_NO] = malloc(sizeof(t_img));
	cub->img[ID_SO] = malloc(sizeof(t_img));
	cub->img[ID_WE] = malloc(sizeof(t_img)); 
	cub->img[ID_EA] = malloc(sizeof(t_img)); 
}

int	main(int argcnt, char **args)
{
	
	t_cub3d	cub;

	if (argcnt != 2)
	{
		write(2, "Error: Incorrect arguments!\n", 28);
		return (EXIT_FAILURE);
	}
	cub3d_init(&cub);
	
	if (map_init(args[1], &cub))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}