#include "cub3d.h"

int	is_ext_xpm(t_parser *p)
{
	if (p->line && (ft_strlen(p->line) > 4) &&
		(ft_strncmp(&(p->line)[ft_strlen(p->line) - 5], ".xpm", 4) 
		== 0))
		return (1);
	return(0);
}

int is_rgb_color(t_cub3d *cub, t_parser *p, int i)
{
	int nbr;

	if (!p->split[i])
	{
		p->status = 4; // Error: missing RGB color in the map
		return (EXIT_FAILURE);
	}
	if (ft_atoi_ext(p->split[i], &nbr))
	{
		if ((nbr < 0) || (nbr > 255))
		{
			p->status = 6; //Error: RGB color smaller than 0 or biger than 255
			return (EXIT_FAILURE);
		}
		else if (i == 0)
			cub->color[p->ident].r = nbr;
		else if (i == 1)
			cub->color[p->ident].g = nbr;
		else if (i == 2)
			cub->color[p->ident].b = nbr;
		printf("rgb_Color :%d \n",nbr);
	}
	else
	{
		p->status = 5; //Error: RGB color is not digit
		return (EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}
