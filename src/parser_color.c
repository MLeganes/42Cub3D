#include "cub3d.h"

static void map_find_rgb(t_cub3d *cub, t_parser *p)
{
	int	i;
	(void)cub;

	p->split = ft_split(p->line, ',');
	if (p->split[0][0] == '\0')
	{
		p->status = 4; // Error: missing RGB color in the map
		return ;
	}
	i = 0;
	while(i < 3)
	{
		//check only for numbers between 0-255 and 3 numbers.
		//if ( p->split[i] && ft_isdigit(p->split[i][0]) &&  (ft_atoi(p->split[i]) >= 0) && (ft_atoi(p->split[i]) < 256)) 
		if (is_rgb_color(p, i)) 
			return ;
		printf("Color split[x]:%d \n",  ft_atoi(p->split[i]));
		i++;
	}

	// printf("Color split[1]:%d \n",  ft_atoi(p->split[1]));
	// printf("Color split[2]:%d \n",  ft_atoi(p->split[2]));
	// 3 digits color.
	//translate to 
}

static void map_find_color(t_cub3d *cub, t_parser *p)
{
	while(p->line && (p->status == -1))
	{
		if (ft_strnstr(p->line, ident2str(p->ident),
			ft_strlen(ident2str(p->ident))))
		{
			printf("......Found color line:%s \n", p->line);
			p->start_line = p->line; //copy the address to free after.
			p->line++;
			while(p->line && *(p->line) && ft_strchr(" \t\r", *(p->line)))
				p->line++;
			printf("......Found color no-spaces:%s \n", p->line);
			if (cub->color[p->ident].used == COLOR_NO_USED)
			{
				map_find_rgb(cub, p);
			}
			else
			{
				p->status = 3; //Error: color is repited in the map\n"));
			}
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
	
	parser_init(&pars, ident); // delete it before using!!!!!!!!
	pars.fd = open(cub_map, O_RDONLY);
	if (pars.fd == -1)
		return (error_exit_failure("Error: No such file or directory\n"));	
	//Read the first line and call the function, due to 25 lines, function cut and t_parser.
	pars.line = get_next_line(pars.fd);
	map_find_color(cub, &pars);
		close(pars.fd);
	//if (pars.line != NULL)
		//free(pars.line);
	if (pars.status == -1) // No change the INIT_STATE, no found.
		return(error_exit_failure("Error: missing color identifier in the map\n"));
	// if(pars.status == 2)
	// 	return(error_exit_failure("Error: wrong color range in the map\n"));
	if(pars.status == 3) //used
		return(error_exit_failure("Error: color is repited in the map\n"));
	if(pars.status == 4)
		return(error_exit_failure("Error: missing RGB color in the map\n"));
	if(pars.status == 5)
		return(error_exit_failure("Error: RGB color is not digit\n"));
	if(pars.status == 6)
		return(error_exit_failure("Error: RGB color smaller than 0 or biger than 255\n"));
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
