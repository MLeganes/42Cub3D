#include "cub3d.h"

char	*identcolor2str(t_identcolor ident)
{
	if (ident == ID_C)
		return ("C");
	if (ident == ID_F)
		return ("F");
	return (NULL);
}

static int get_rgb_colornumber(t_cub3d *cub, t_parser *p, int i, t_identcolor id)
{
	int nbr;

	if (ft_atoi_ext(p->split[i], &nbr))
	{
		if ((nbr < 0) || (nbr > 255))
		{
			return (err_fail2("Error: RGB color smaller than 0 or bigger than 255 in ", identcolor2str(id)));
			// p->status = 6; //Error: RGB color smaller than 0 or bigger than 255
			// return (EXIT_FAILURE);
		}
		else if (i == 0)
			cub->color[id].r = nbr;
		else if (i == 1)
			cub->color[id].g = nbr;
		else if (i == 2)
			cub->color[id].b = nbr;
		return(EXIT_SUCCESS);
	}
	else
	{
		return (err_fail2("Error: RGB color is not digit in ", identcolor2str(id)));
		// p->status = 5; //Error: RGB color is not digit
		// return (EXIT_FAILURE);
	}
}


static int get_rgb(t_cub3d *cub, t_parser *p, t_identcolor id)
{
	int	i;

	if ((!p->line) || (ft_strlen(p->line) < 6) || (p->line[0] == '\n'))
	{
		return (err_fail2("Error: something missing in RGB colors in ", identcolor2str(id)));
		// p->status = 4; //Error:[4] something wrong with RGB colors in the map
		// return ;
	}
	p->split = ft_split(p->line, ',');
	i = 0;
	while(i < 3)
	{
		if (!p->split[i])
		{
			return (err_fail2("Error: missing RGB color in the ", identcolor2str(id)));
			// p->status = 4; // Error: missing RGB color in the map
			// return ;
		}
		if (get_rgb_colornumber(cub, p, i, id)) 
			return (EXIT_FAILURE);
		i++;
	}
	if (i == 3)
	{
		cub->color[id].rgb = rgb_to_colorHex(cub->color[id].r,
			cub->color[id].g, cub->color[id].b);
		printf("Color rgb: %d in the %s \n", cub->color[id].rgb, identcolor2str(id));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int identifier_color(t_cub3d *cub, t_parser *p, char c)
{
	printf("\nIDENTIFIER COLOR: %c \n", c);
	p->line = p->map[p->idx];
	p->line++;
	while(p->line && *(p->line) && ft_strchr(" \t\r", *(p->line))) // remove spaces, tab, ....etc
		p->line++;
	//printf("\nColor no-spaces:%s \n", p->line);
	if ( c == 'C')
	{
		printf("color C found: %s\n", p->line);
		if (cub->color[ID_C].used == COLOR_NO_USED)
			return (get_rgb(cub, p, ID_C)); // Line with rgb colors.
		else
			return (err_fail2("Error: color is repited in the map", p->map[p->idx]));
	}
	if (c == 'F')
	{
		printf("color F found: %s\n", p->line);
		if (cub->color[ID_C].used == COLOR_NO_USED)
			return (get_rgb(cub, p, ID_F)); // Line with rgb colors.
		else
			return (err_fail2("Error: color is repited in the map", p->map[p->idx]));
	}
	// else
	// 	p->status = 3; //Error: color is repited in the map\n"));
	// free(p->start_line);
	return (EXIT_SUCCESS);
	//return (err_fail("error: No idea what happen here, it shoud not get in this point\n"));
}
