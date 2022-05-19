/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnies <mnies@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:41:48 by mnies             #+#    #+#             */
/*   Updated: 2022/05/19 15:42:12 by mnies            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parser_check(t_cub3d *cub)
{
	if (cub->color[ID_C].used == COLOR_IN_USE
		&& cub->color[ID_F].used == COLOR_IN_USE
		&& cub->img[ID_SO]->path_tex != NULL
		&& cub->img[ID_NO]->path_tex != NULL
		&& cub->img[ID_WE]->path_tex != NULL
		&& cub->img[ID_EA]->path_tex != NULL
		&& cub->rotation != -1)
	{
		printf("\n\n **** PARSING CHECKING *****\n\n");
		printf("texture NO %s\n", cub->img[ID_NO]->path_tex);
		printf("texture SO %s\n", cub->img[ID_SO]->path_tex);
		printf("texture WE %s\n", cub->img[ID_WE]->path_tex);
		printf("texture EA %s\n", cub->img[ID_EA]->path_tex);
		printf("color C %d\n", cub->color[ID_C].rgb);
		printf("color F %d\n", cub->color[ID_F].rgb);
		printf("player rot %d\n", cub->rotation);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

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
	while (i < (p->nolines + 1))
	{
		if (p->map[i])
			free(p->map[i]);
		i++;
	}
	if (p->map)
		free(p->map);
	p->map = NULL;
	free_split(p);
	return (EXIT_SUCCESS);
}

void	parser_init(t_parser *pars)
{
	pars->fd = -1;
	pars->line = NULL;
	pars->split = NULL;
	pars->nolines = 0;
	pars->idx = 0;
	pars->map = NULL;
	pars->player = '\0';
}

int	parser(char *path, t_cub3d *cub)
{
	t_parser	pars;

	parser_init(&pars);
	if (is_ext_cub(path))
		return (EXIT_FAILURE);
	if (parser_readfd(&pars, path))
		return (EXIT_FAILURE);
	if (parser_identifier(cub, &pars))
		return (EXIT_FAILURE);
	if (parser_map(cub, &pars))
		return (EXIT_FAILURE);
	if (parser_check(cub))
		return (err_fail("Missing some parameter in cub file"));
	if (parser_free(&pars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
