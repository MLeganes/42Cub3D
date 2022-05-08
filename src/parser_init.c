#include "cub3d.h"

void	parser_init(t_parser *pars, t_identifier ident)
{
	pars->fd = -1;
	pars->status = -1; // INIT_POINT
	pars->ident = ident;
	pars->line = NULL;
	pars->start_line = NULL;
	pars->split = NULL;
}
