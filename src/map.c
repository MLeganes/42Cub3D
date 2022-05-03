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
	if (split[1] && (ft_strlen(split[1]) > 4) && ( ft_strncmp(&(split[1])[ft_strlen(split[1]) - 5], ".xpm", 4) == 0))
	{		
		cub->img[ident]->path_tex = ft_strdup(split[1]);
		free(line);
		free(split);
		return (EXIT_SUCCESS);
	}
	else
	{
		free(line);
		free(split);
		printf("Error: wrong extension in theme %s\n", ident2str(ident));
		return(error_exit_failure("Error: wrong extension in the theme\n"));
	}
}

int	map_find_identifier(t_cub3d *cub, t_identifier ident, char *cub_map)
{
	int		fd;
	int		find;
	char	*line;

	line = NULL;
	fd = open(cub_map, O_RDONLY);
	if (fd == -1)
		return (error_exit_failure("Error: No such file or directory"));
	line = get_next_line(fd);
	// if (line == NULL)
	// 	return(error_exit_failure("Error: map is empty\n"));
	find = 1;
	while(line && find)
	{
		if (ft_strnstr(line, ident2str(ident), ft_strlen(ident2str(ident))))
		{
			find = 0;
			map_get_xpm_path(cub, ident, line);
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
		return(error_exit_failure("Error: wrong extension in the map path\n"));
	if (map_get_imgs_path(cub, path))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
