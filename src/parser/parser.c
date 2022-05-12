#include "cub3d.h"

int parser_free(t_parser *p)
{
	(void)p;

	return (EXIT_SUCCESS);
}

int parser_fullcheck(t_cub3d *cub, t_parser *p)
{
	(void)p;
	(void)cub;
	//if (cub->color[ID_C].used == COLOR_IN_USE &&)

	return (EXIT_SUCCESS);
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
	if (parser_fullcheck(cub, &pars))
		return (EXIT_FAILURE);
	if (parser_free(&pars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
