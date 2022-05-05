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

// Check if the line start with the "NO" identier. If yes, extract the path.
static void map_find_path_xpm(t_cub3d *cub, t_parser *p)
{
	while(p->line && (p->status == -1))
	{
		if (ft_strnstr(p->line, ident2str(p->ident),
			ft_strlen(ident2str(p->ident))))
		{
			p->start_line = p->line; //copy the address to free after.
			p->line = p->line + 2;
			while(p->line && *(p->line) && ft_strchr(" \t\r", *(p->line)))
				p->line++;
			if(is_ext_xpm(p))
			{
				cub->img[p->ident]->path_tex = ft_strdup(p->line); 
				printf("......Found path theme: %s \n", cub->img[p->ident]->path_tex);
				p->status = 0;
			}
			else
				p->status = 2; //Error: wrong path or wrong extension in the theme\n
			free(p->start_line);
		}
		if (p->status == -1)
		{
			free(p->line);
			p->line = get_next_line(p->fd);
		}
	}
}

/****
 * status:
 * 
 * 				INIT_STATE		-1	// Starting point
 * 				EXIT_SUCESS		0
 * 				EXIT_FAILURE	1
 * 				ERROR			2
 * 				...
 * 				FIND_WHATEVER	50
 * 
 * 
 */
static int	map_find_identifier(t_cub3d *cub, t_identifier ident, char *cub_map)
{
	t_parser pars;
	
	parser_init(&pars, ident);
	pars.fd = open(cub_map, O_RDONLY);
	if (pars.fd == -1)
		return (error_exit_failure("Error: No such file or directory\n"));
	
	//Read the first line and call the function, due to 25 lines, function cut and t_parser.
	pars.line = get_next_line(pars.fd);
	map_find_path_xpm(cub, &pars);
	
	close(pars.fd);
	//if (pars.line != NULL)
		//free(pars.line);
	if (pars.status == -1)
		return(error_exit_failure("Error: missing identifier for the texture in the map\n"));
	if(pars.status == 2)
		return(error_exit_failure("Error: wrong extension in the texture\n"));
	return (EXIT_SUCCESS);
}

int	parser_texture(t_cub3d *cub, char *path_cub)
{
	if (map_find_identifier(cub, ID_NO, path_cub))
		return (EXIT_FAILURE);
	if (map_find_identifier(cub, ID_SO, path_cub))
		return (EXIT_FAILURE);
	if (map_find_identifier(cub, ID_WE, path_cub))
		return (EXIT_FAILURE);
	if (map_find_identifier(cub, ID_EA, path_cub))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}