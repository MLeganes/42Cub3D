/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:41:15 by mnies             #+#    #+#             */
/*   Updated: 2022/05/19 17:15:50 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ident2str(t_identifier ident)
{
	if (ident == ID_NO)
		return ("NO");
	if (ident == ID_SO)
		return ("SO");
	if (ident == ID_WE)
		return ("WE");
	if (ident == ID_EA)
		return ("EA");
	return (NULL);
}

static int	identifier_texture(t_cub3d *cub, t_parser *p, t_identifier id)
{
	p->line = p->map[p->idx];
	p->line = p->line + 2;
	while (p->line && *(p->line) && ft_strchr(" \t\r", *(p->line)))
		p->line++;
	if (is_ext_xpm(p) == EXIT_SUCCESS)
	{
		if (cub->img[id]->path_tex == NULL)
		{
			cub->img[id]->path_tex = ft_strdup(p->line);
			cub->img[id]->path_tex[ft_strlen(p->line) - 1] = '\0';
			if (is_path(cub->img[id]->path_tex))
				return (EXIT_FAILURE);
			p->line = NULL;
			return (EXIT_SUCCESS);
		}
		else
			return (err_fail2("Texture repited ", p->line));
	}
	return (EXIT_FAILURE);
}

static int	identifier_selector(t_cub3d *cub, t_parser *p)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (ft_strnstr(p->map[p->idx], ident2str(i), 2))
		{
			if (identifier_texture(cub, p, i))
				return (EXIT_FAILURE);
		}
		i++;
	}
	if ((p->map[p->idx][0] == 'C') || (p->map[p->idx][0] == 'F'))
	{
		if (identifier_color(cub, p, p->map[p->idx][0]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser_identifier(t_cub3d *cub, t_parser *p)
{
	p->idx = 0;
	while (p->map[p->idx])
	{
		if (identifier_selector(cub, p))
			return (EXIT_FAILURE);
		p->idx++;
	}
	return (EXIT_SUCCESS);
}
