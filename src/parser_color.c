#include "cub3d.h"

static void map_find_rgb(t_cub3d *cub, t_parser *p)
{
	int	i;

	p->split = ft_split(p->line, ',');
	i = 0;
	while(i < 3)
	{
		if (is_rgb_color(cub, p, i)) 
			return ;
		i++;
	}
	if (i == 3)
	{
		p->status = 0;
	}
}

static void map_find_colorId(t_cub3d *cub, t_parser *p)
{
	// find line with C or F
	while(p->line && (p->status == -1))
	{
		// LIne with C or F
		if (ft_strnstr(p->line, ident2str(p->ident),
			ft_strlen(ident2str(p->ident))))
		{
			printf("......Found color line:%s \n", p->line);
			p->start_line = p->line; //copy the address to free after.
			p->line++;
			while(p->line && *(p->line) && ft_strchr(" \t\r", *(p->line))) // remove spaces, tab, ....etc
				p->line++;
			printf("......Found color no-spaces:%s \n", p->line);
			if (cub->color[p->ident].used == COLOR_NO_USED)
			{
				if ( (!p->line) || (ft_strlen(p->line) < 6) || (p->line[0] == '\n') )
					p->status = 4; //Error:[4] something wrong with RGB colors in the map
				else
					map_find_rgb(cub, p); // Line with rgb colors.
			}
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
		return(error_exit_failure("Error: wrong range: RGB color smaller than 0 or biger than 255\n"));
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
