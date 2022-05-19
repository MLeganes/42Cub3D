/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnies <mnies@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:41:34 by mnies             #+#    #+#             */
/*   Updated: 2022/05/19 15:41:35 by mnies            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (err_fail2("No such file or directory ", path));
	close(fd);
	return (EXIT_SUCCESS);
}

int	is_ext_xpm(t_parser *p)
{
	if (p->line && (ft_strlen(p->line) > 4)
		&& (ft_strncmp(&(p->line)[ft_strlen(p->line) - 5], ".xpm", 4) == 0))
	{
		return (EXIT_SUCCESS);
	}
	return (err_fail2("Wrong extension in the ", p->line));
}

int	is_ext_cub(char *pth)
{
	if (ft_strlen(pth) > 4 && ft_strncmp(&pth[ft_strlen(pth) - 4], ".cub", 4))
		return (err_fail2("Wrong extension in the ", pth));
	return (EXIT_SUCCESS);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

void	remove_eol(t_parser *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == '\n')
				p->map[i][j] = '\0';
			j++;
		}
		i++;
	}
	return ;
}
