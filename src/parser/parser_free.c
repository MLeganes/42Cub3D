/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:08:47 by amorcill          #+#    #+#             */
/*   Updated: 2022/05/19 18:59:43 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(t_parser *p)
{
	int	i;

	i = 0;
	if (p->split != NULL)
	{
		while (p->split[i])
		{
			free(p->split[i]);
			p->split[i] = NULL;
			i++;
		}
		free(p->split);
	}
	p->split = NULL;
}

int	parser_free(t_parser *p)
{
	int	i;

	i = 0;
	if (p->map != NULL)
	{
		while (i < (p->nolines + 1))
		{
			if (p->map[i])
				free(p->map[i]);
			i++;
		}
	}
	if (p->map)
		free(p->map);
	p->map = NULL;
	free_split(p);
	return (EXIT_SUCCESS);
}

int	parser_free_return(t_parser *par, int ret_status)
{
	parser_free(par);
	return (ret_status);
}
