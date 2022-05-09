#include "cub3d.h"

int	is_ext_xpm(t_parser *p)
{
	if (p->line && (ft_strlen(p->line) > 4) &&
		(ft_strncmp(&(p->line)[ft_strlen(p->line) - 5], ".xpm", 4) 
		== 0))
		return (1);
	return(0);
}

int	is_ext_cub(char *path)
{
	if (ft_strlen(path) > 4 && ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4))
		return(err_fail("Error: wrong extension in the .cub map\n"));
	return(EXIT_SUCCESS);
}
