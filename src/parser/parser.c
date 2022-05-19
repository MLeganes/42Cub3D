/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:41:48 by mnies             #+#    #+#             */
/*   Updated: 2022/05/19 18:59:09 by amorcill         ###   ########.fr       */
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
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	parser_init(t_parser *pars)
{
	pars->fd = -1;
	pars->line = NULL;
	pars->split = NULL;
	pars->map = NULL;
	pars->idx = 0;
	pars->imap = 0;
	pars->nolines = 0;
	pars->player = '\0';
}

int	parser(char *path, t_cub3d *cub)
{
	t_parser	pars;

	parser_init(&pars);
	if (is_ext_cub(path))
		return (parser_free_return(&pars, EXIT_FAILURE));
	if (parser_readfd(&pars, path))
		return (parser_free_return(&pars, EXIT_FAILURE));
	if (parser_identifier(cub, &pars))
		return (parser_free_return(&pars, EXIT_FAILURE));
	if (parser_map(cub, &pars))
		return (parser_free_return(&pars, EXIT_FAILURE));
	if (parser_check(cub))
	{
		parser_free(&pars);
		return (err_fail("Missing some parameter in cub file\n"));
	}
	parser_free(&pars);
	return (EXIT_SUCCESS);
}
