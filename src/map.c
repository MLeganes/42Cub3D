/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:53:07 by amorcill          #+#    #+#             */
/*   Updated: 2022/05/03 01:50:34 by amorcill         ###   ########.fr       */
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
	return (NULL);
}

static int map_get_xpm_path(t_cub3d *cub, t_identifier ident, char *line)
{
	char	**split;
	
	split = ft_split(line, ' ');
	if ( split[1] && (ft_strlen(split[1]) > 4) && ( ft_strncmp(&(split[1])[ft_strlen(split[1]) - 5], ".xpm", 4) == 0))
	{
		printf("Split[1] and extension CORRECT!!!: %s \n", split[1]);
		cub->img[ident]->path_tex = split[1];
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	map_find_identifier(t_cub3d *cub, t_identifier ident, char *cub_map)
{
	int		fd;
	int		find;
	char	*line;

	line = NULL;
	fd = open(cub_map, O_RDONLY);
	if (fd == -1)
	{
		perror("map");
		return (error_exit_failure("Error: fail to read map\n"));
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
			find = 0;
			map_get_xpm_path(cub, ident, line);
			cub->img[ident]->path_tex = ft_strdup(line);
			close(fd);
			return (EXIT_SUCCESS);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (EXIT_FAILURE);
}

int map_get_imgs_path(t_cub3d *cub, char *cub_map)
{
	if (map_find_identifier(cub, ID_NO, cub_map))
		return (EXIT_FAILURE);
	if (map_find_identifier(cub, ID_SO, cub_map))
		return (EXIT_FAILURE);
	if (map_find_identifier(cub, ID_WE, cub_map))
		return (EXIT_FAILURE);
	if (map_find_identifier(cub, ID_EA, cub_map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	map_init(char *path, t_cub3d *cub)
{
	if (ft_strlen(path) > 4 && ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4))
	{
		perror("map"); //I donot understand the perror!!!!
		return(write(2, "Error: no valid map path or wrong extension\n", 45));
	}
	if (map_get_imgs_path(cub, path))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
