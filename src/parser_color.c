#include "cub3d.h"

static int get_rgb_colornumber(t_cub3d *cub, t_parser *p, int i)
{
	int nbr;

	if (ft_atoi_ext(p->split[i], &nbr))
	{
		if ((nbr < 0) || (nbr > 255))
		{
			p->status = 6; //Error: RGB color smaller than 0 or bigger than 255
			return (EXIT_FAILURE);
		}
		else if (i == 0)
			cub->color[p->ident].r = nbr;
		else if (i == 1)
			cub->color[p->ident].g = nbr;
		else if (i == 2)
			cub->color[p->ident].b = nbr;
	}
	else
	{
		p->status = 5; //Error: RGB color is not digit
		return (EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}

static void map_find_rgb(t_cub3d *cub, t_parser *p)
{
	int	i;

	if ( (!p->line) || (ft_strlen(p->line) < 6) || (p->line[0] == '\n'))
	{
		p->status = 4; //Error:[4] something wrong with RGB colors in the map
		return ;
	}
	p->split = ft_split(p->line, ',');
	i = 0;
	while(i < 3)
	{
		if (!p->split[i])
		{
			p->status = 4; // Error: missing RGB color in the map
			return ;
		}
		if (get_rgb_colornumber(cub, p, i)) 
			return ;
		i++;
	}
	if (i == 3)
	{
		cub->color[p->ident].rgb = rgb_to_colorHex(cub->color[p->ident].r,
			cub->color[p->ident].g, cub->color[p->ident].b);
		p->status = 0;
		printf("......color rgb:%d \n", cub->color[p->ident].rgb);
	}
}

static void map_find_colorId(t_cub3d *cub, t_parser *p)
{
	while(p->line && (p->status == -1))
	{
		if (ft_strnstr(p->line, ident2str(p->ident),
			ft_strlen(ident2str(p->ident))))
		{
			p->start_line = p->line; //copy the address to free after.
			p->line++;
			while(p->line && *(p->line) && ft_strchr(" \t\r", *(p->line))) // remove spaces, tab, ....etc
				p->line++;
			printf("......Found color no-spaces:%s \n", p->line);
			if (cub->color[p->ident].used == COLOR_NO_USED)
				map_find_rgb(cub, p); // Line with rgb colors.
			else
				p->status = 3; //Error: color is repited in the map\n"));
			free(p->start_line);
		}
		if (p->status == -1) // No yet color found, keep looking until find or end.
		{
			free(p->line);
			p->line = get_next_line(p->fd);
		}
	}
}

static int	map_find_identifier(t_cub3d *cub, t_identifier ident, char *cub_map)
{
	t_parser pars;
	
	parser_init(&pars, ident); // delete it before using!!!!!!!! _> Nothing is mallocing, so and the end of the func. is deleted!!!
	pars.fd = open(cub_map, O_RDONLY);
	if (pars.fd == -1)
		return (error_exit_failure("Error: No such file or directory\n"));
	pars.line = get_next_line(pars.fd);
	map_find_colorId(cub, &pars);
	close(pars.fd);

	if (pars.status == -1) // No change the INIT_STATE, no found.
		return(error_exit_failure("Error: missing color identifier in the map\n"));
	// if(pars.status == 2)
	// 	return(error_exit_failure("Error: wrong color range in the map\n"));
	if(pars.status == 3) //used
		return(error_exit_failure("Error: color is repited in the map\n"));
	if(pars.status == 4)
		return(error_exit_failure("Error:[4] something wrong with RGB colors in the map\n"));
	if(pars.status == 5)
		return(error_exit_failure("Error: RGB color is not digit\n"));
	if(pars.status == 6)
		return(error_exit_failure("Error: wrong range: RGB color smaller than 0 or bigger than 255\n"));
	return (EXIT_SUCCESS);
}

int	parser_color(t_cub3d *cub, char *path_cub)
{
	if (map_find_identifier(cub, ID_C, path_cub))
		return (EXIT_FAILURE);
	if (map_find_identifier(cub, ID_F, path_cub))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
