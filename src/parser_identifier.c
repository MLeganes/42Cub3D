#include "cub3d.h"

char	*ident2str(t_identifier ident)
{
	if (ident == ID_NO)
		return ("NO");
	if (ident == ID_SO)
		return ("SO");
	if (ident == ID_WE)
		return ("WE");
	if (ident == ID_EA)
		return ("EA");
	return (NULL);
}

// Check if the line start with the "NO" identier. If yes, extract the path.
// static void map_find_path_xpm(t_cub3d *cub, t_parser *p)
// {
// 	while(p->line && (p->status == -1))
// 	{
// 		if (ft_strnstr(p->line, ident2str(p->ident),
// 			ft_strlen(ident2str(p->ident))))
// 		{
// 			p->start_line = p->line; //copy the address to free after.
// 			p->line = p->line + 2;
// 			while(p->line && *(p->line) && ft_strchr(" \t\r", *(p->line)))
// 				p->line++;
// 			if(is_ext_xpm(p))
// 			{
// 				// if (cub->img[p->ident]->path_tex == NULL)
// 				// {
// 					cub->img[p->ident]->path_tex = ft_strdup(p->line);
// 					p->status = 0;
// 					printf("......Found path theme: %s \n", cub->img[p->ident]->path_tex);
// 				// }
// 				// else
// 				// 	p->status = 3; //Texture repited, error!!!!!
// 			}
// 			else
// 				p->status = 2; //Error: wrong path or wrong extension in the theme\n
// 			free(p->start_line);
// 		}
// 		if (p->status == -1)
// 		{
// 			free(p->line);
// 			p->line = get_next_line(p->fd);
// 		}
// 	}
// }

static int identifier_texture(t_cub3d *cub, t_parser *p, t_identifier id)
{
	(void)cub;
	(void)p;
	(void)id;

	printf("%i %s \n",p->idx, p->map[p->idx]);
	return (EXIT_SUCCESS);
}

static int	identifier_selector(t_cub3d *cub, t_parser *p)
{
	

	if (ft_strnstr(p->map[p->idx], ident2str(ID_NO), 2))
		identifier_texture(cub, p, ID_NO);
	else if (ft_strnstr(p->map[p->idx], ident2str(ID_SO), 2))
		identifier_texture(cub, p, ID_SO);
	else if (ft_strnstr(p->map[p->idx], ident2str(ID_WE), 2))
		identifier_texture(cub, p, ID_WE);
	else if (ft_strnstr(p->map[p->idx], ident2str(ID_EA), 2))
		identifier_texture(cub, p, ID_EA);

	// else if (ft_strnstr(p->map[p->idx], "C", 1))
	// 	identifier_color(cub, p, 'C');
	// else if (ft_strnstr(p->map[p->idx], "F", 1))
	// 	identifier_color(cub, p, 'F');
	
	//map_find_path_xpm(cub, &pars);
	// if (p.status == -1)
	// 	return(err_fail("Error: missing identifier for the texture in the map\n"));
	// if(p.status == 2)
	// 	return(err_fail("Error: wrong extension in the texture\n"));
	// if(p.status == 3)
	// 	return(err_fail("Error: texture repited in the map\n"));
	return (EXIT_SUCCESS);
}

int	parser_identifier(t_cub3d *cub, t_parser *p)
{
	p->idx = 0;
	(void)cub;

	while (p->map[p->idx])
	{
		if (identifier_selector(cub, p))
			return (EXIT_FAILURE);
		p->idx++;
	}
	return (EXIT_SUCCESS);
}
