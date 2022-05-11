# include "cub3d.h"

void	parser_init(t_parser *pars)
{
	pars->fd = -1;
	pars->line = NULL;
	pars->split = NULL;
	pars->nolines = 0;
	pars->idx = 0;
	pars->map = NULL;
}

int parser(char *path, t_cub3d *cub)
{
	t_parser pars;
	
	parser_init(&pars); 

	if (is_ext_cub(path))
		return(EXIT_FAILURE);

	if (parser_readfd(&pars, path))
		return (EXIT_FAILURE);

	if (parser_identifier(cub, &pars))
		return (EXIT_FAILURE);
	if (parser_map(cub, &pars, path))
		return (EXIT_FAILURE);

	/**
	 * @todos 
	 * 
	 *    1). Check if there are all texture and color in the struct, before keep going
	 *    2). 
	 * 
	 */

	// free_parser(&parser);//If needed, yes map!!
	return (EXIT_SUCCESS);
}
