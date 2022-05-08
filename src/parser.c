# include "cub3d.h"

int parser(char *path, t_cub3d *cub)
{
	if (ft_strlen(path) > 4 && ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4))
		return(error_exit_failure("Error: wrong extension in the .cub map\n"));

	if (parser_texture(cub, path))
		return (EXIT_FAILURE);
	
	if (parser_color(cub, path))
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
