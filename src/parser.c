# include "cub3d.h"

void	parser_init(t_parser *pars, t_identifier ident)
{
	pars->fd = -1;
	pars->status = -1; // INIT_POINT
	pars->ident = ident;
	pars->line = NULL;
	pars->start_line = NULL;
	pars->split = NULL;
	pars->nolines = 0;
	pars->idx = 0;
	pars->map = NULL;
}

int parser(char *path, t_cub3d *cub)
{
	t_parser pars;
	int		i;

	(void)cub;
	
	parser_init(&pars, ID_NONE); 
	if (is_ext_cub(path))
		return(EXIT_FAILURE);

	if (parser_readfd(&pars, path))
		return (EXIT_FAILURE);
	

	// testing
	printf("Lines in .cub file: %d\n", pars.nolines);
	i =0;
	printf("........PRINT MY FILE IN MEMORY\n");
	while ( pars.map && pars.map[i])
	{
		printf("%i %s",i, pars.map[i]);
		i++;
		/* code */
	}
	//end testing
	

	// if (parser_identifiers(cub, path))
	// 	return (EXIT_FAILURE);
	// if (parser_map(cub, path))
	// 	return (EXIT_FAILURE);

	// free_parser(&parser);//If needed, yes map!!
	return (EXIT_SUCCESS);
}
