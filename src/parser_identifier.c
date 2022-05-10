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

static int identifier_texture(t_cub3d *cub, t_parser *p, t_identifier id)
{
	p->line = p->map[p->idx];
	if (ft_strnstr(p->line, ident2str(id),
		ft_strlen(ident2str(id))))
	{
		p->line = p->line + 2;
		while(p->line && *(p->line) && ft_strchr(" \t\r", *(p->line)))
			p->line++;
		p->line[ft_strlen(p->line) - 1] = '\0'; //remove \n
		if(is_ext_xpm(p) == EXIT_SUCCESS)
		{
			if (cub->img[id]->path_tex == NULL)
			{
				cub->img[id]->path_tex = ft_strdup(p->line);
				printf("Paht for the img %s \n", cub->img[id]->path_tex);
				p->status = 0;
				return (EXIT_SUCCESS);
			}
			else
				return (err_fail2("Error: Texture repited ", p->line)); //p->status = 3; //Texture repited, error!!!!!
		}
		else
			return (EXIT_FAILURE);	//Error: wrong path or wrong extension in the theme\n
	}
	p->line = NULL;
	return (EXIT_SUCCESS);
}

static int	identifier_selector(t_cub3d *cub, t_parser *p)
{
	if (ft_strnstr(p->map[p->idx], ident2str(ID_NO), 2))
	{
		if (identifier_texture(cub, p, ID_NO))
			return (EXIT_FAILURE);
	}
	else if (ft_strnstr(p->map[p->idx], ident2str(ID_SO), 2))
	{
		if (identifier_texture(cub, p, ID_SO))
			return (EXIT_FAILURE);
	}
	else if (ft_strnstr(p->map[p->idx], ident2str(ID_WE), 2))
	{
		if (identifier_texture(cub, p, ID_WE))
			return (EXIT_FAILURE);
	}
	else if (ft_strnstr(p->map[p->idx], ident2str(ID_EA), 2))
	{
		if (identifier_texture(cub, p, ID_EA))
			return (EXIT_FAILURE);
	}
	//else if ( ft_strnstr(p->map[p->idx], "C", 1) || ft_strnstr(p->map[p->idx], "F", 1))
	else if ((p->map[p->idx][0] == 'C') || (p->map[p->idx][0] == 'F'))
	{
		if (identifier_color(cub, p, p->map[p->idx][0]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);

	//map_find_path_xpm(cub, &pars);
	// if (p.status == -1)
	// 	return(err_fail("Error: missing identifier for the texture in the map\n"));
	// if(p.status == 2)
	// 	return(err_fail("Error: wrong extension in the texture\n"));
	// if(p.status == 3)
	// 	return(err_fail("Error: texture repited in the map\n"));
}

int	parser_identifier(t_cub3d *cub, t_parser *p)
{
	p->idx = 0;

	while (p->map[p->idx])
	{
		if (identifier_selector(cub, p))
			return (EXIT_FAILURE);
		p->idx++;
	}
	return (EXIT_SUCCESS);
}
