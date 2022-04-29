/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:28:28 by amorcill          #+#    #+#             */
/*   Updated: 2022/04/29 16:56:13 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argcnt, char **args)
{
	t_cub3d	cub;

	if (argcnt != 2)
	{
		write(2, "Error: Incorrect arguments!\n", 28);
		return (EXIT_FAILURE);
	}

	if (map_init(args[1], &cub))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}