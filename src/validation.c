#include "cub3d.h"

int	is_ext_xpm(t_parser *p)
{
	if (p->line && (ft_strlen(p->line) > 4) &&
		(ft_strncmp(&(p->line)[ft_strlen(p->line) - 5], ".xpm", 4) 
		== 0))
		return (1);
	return(0);
}

int is_rgb_color(t_parser *p, int i)
{
	if (!p->split[i])
	{
		p->status = 4; // Error: missing RGB color in the map
		return (EXIT_FAILURE);
	}
	if (!ft_isdigit(p->split[i][0]) )
	{
		p->status = 5; //Error: RGB color is not digit
		return (EXIT_FAILURE);
	}
	if ((ft_atoi(p->split[i]) < 0) || (ft_atoi(p->split[i]) > 255))
	{
		p->status = 6; //Error: RGB color smaller than 0 or biger than 255
		return (EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}
