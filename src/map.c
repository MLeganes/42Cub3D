/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:53:07 by amorcill          #+#    #+#             */
/*   Updated: 2022/04/29 16:53:09 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ident2str(t_identifier ident)
{
	if (ident == ID_NO)
		return ("NO");
	else if (ident == ID_SO)
		return ("SO");
	else if (ident == ID_WE)
		return ("WE");
	else if (ident == ID_EA)
		return ("EA");
	else if (ident == ID_F)
		return ("F");
	else if (ident == ID_C)
		return ("C");
}


int	map_find_identifier(t_cub3d *cub, t_identifier ident, char *cub_map, char *line)
{
	int		fd;
	int		find;
	char	*line;

	line = NULL;
	cub->img_ea = -1;

	fd = open(cub_map, O_RDONLY);
	if (fd == -1)
	{
		perror("map");
		write(2, "Error: fail to read map\n", 25);
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (line == NULL)
		exit(write(2, "Error: empty map file\n", 22));
	find = 1;
	while(line && find)
	{
		if (ft_strnstr(line, ident2str(ident), ft_strlen(ident2str(ident))))
		{
			printf("Mapa line looking for %s name: %s",ident2str(ident), line);
			find = 1;
			cub->img[ident]->path_tex = ft_strdup(line);
			return (EXIT_SUCCESS);
		}
		free(line);
		line = get_next_line(fd);
	}
	return EXIT_FAILURE;
}

int map_get_imgs_path(t_cub3d *cub, char *cub_map)
{
	char	*line;
	char	*splitline;
	char	*tmpline;
	
	if (map_find_identifier(cub, ID_NO, cub_map, &line) )
	{
		return (EXIT_FAILURE);
	}
	else
	{
		// here is the line with the coinciden of the name., 
		// needed to split, get the path, check the path and free line.
		splitline = ft_split(line, ' ');
		if (splitline[1] == NULL)
		{
			//ERROR, no path for the theme
			return (EXIT_FAILURE);
		}
		else
		{
			// check path
			cub->img_no = ft_strdup(splitline[1]);//free in the free-structure
			free(splitline);
			if (!(ft_strlen(cub->img_no) > 4 && ft_strncmp(&cub->img_no[ft_strlen(cub->img_no) - 4], ".xpm", 4)))
			{
				//ERROR, wrong extension for theme
				return (EXIT_FAILURE);				
			}


		}
	}
	return (EXIT_SUCCESS);
}

int	map_init(char *path, t_cub3d *cub)
{
	if (ft_strlen(path) > 4 && ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4))
	{
		perror("map"); //I donot understand the perror!!!!

		//exit(write(2, "Error: map file no valid path or wrong extension", 21));
		return(write(2, "Error: no valid map path or wrong extension\n", 45));
	}
	if (map_get_imgs_path(cub, path))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
