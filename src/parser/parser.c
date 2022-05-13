#include "cub3d.h"

int parser_free(t_parser *p)
{
	int i;

	if (p->map != NULL)
	{
		free(p->map);
		p->map = NULL;
	}
	if (p->line != NULL)
	{
		free(p->line);
		p->line = NULL;
	}
	i = 0;
	if (p->split != NULL)
	{
		while (p->split[i])
		{
			free(p->split[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int parser_check(t_cub3d *cub)
{
	if (cub->color[ID_C].used == COLOR_IN_USE
		&& cub->color[ID_F].used == COLOR_IN_USE
		&& cub->img[ID_SO]->path_tex != NULL
		&& cub->img[ID_NO]->path_tex != NULL
		&& cub->img[ID_WE]->path_tex != NULL
		&& cub->img[ID_EA]->path_tex != NULL
		&& cub->player != 0)
			return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	parser_init(t_parser *pars)
{
	pars->fd = -1;
	pars->line = NULL;
	pars->split = NULL;
	pars->nolines = 0;
	pars->idx = 0;
	pars->map = NULL;
	pars->player = '\0';
}

int	parser(char *path, t_cub3d *cub)
{
	t_parser	pars;

	parser_init(&pars);
	if (is_ext_cub(path))
		return (EXIT_FAILURE);
	if (parser_readfd(&pars, path))
		return (EXIT_FAILURE);
	if (parser_identifier(cub, &pars))
		return (EXIT_FAILURE);
	if (parser_map(cub, &pars))
		return (EXIT_FAILURE);
	/**
	 * @todos 
	 * 
	 *    1). Check if there are all texture and color in the struct, before keep going
	 *    2). free_parser(&parser);//If needed, yes map!!
	 * 
	 */
	if (parser_check(cub))
		return (err_fail("Missing some parameter in cub file"));
	if (parser_free(&pars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
