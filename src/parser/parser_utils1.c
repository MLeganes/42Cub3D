#include "cub3d.h"

// int	color_rgb(int r, int g, int b)
// {
// 	int	color;

// 	color = 0;
// 	color += r << 16;
// 	color += g << 8;
// 	color += b;
// 	return (color);
// }

int	is_ext_xpm(t_parser *p)
{
	int fd;

	if (p->line && (ft_strlen(p->line) > 4) &&
		(ft_strncmp(&(p->line)[ft_strlen(p->line) - 4], ".xpm", 4) 
		== 0))
	{
		fd = open(p->line, O_RDONLY);
		if (fd == -1)
		 	return (err_fail2("Error: No such file or directory ", p->line));
		close(fd);
		return (EXIT_SUCCESS);
	}
	return (err_fail2("Error: Wrong extension in the ", p->line));
}

int	is_ext_cub(char *pth)
{
	if (ft_strlen(pth) > 4 && ft_strncmp(&pth[ft_strlen(pth) - 4], ".cub", 4))
		return(err_fail2("Error: Wrong extension in the ", pth));
	return(EXIT_SUCCESS);
}