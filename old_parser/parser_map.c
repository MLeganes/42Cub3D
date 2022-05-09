#include "cub3d.h"

int	parser_map(t_cub3d *cub, char *path_cub)
{
	t_parser pars;

	parser_init(&pars, ID_MAP);
	pars.fd = open(path_cub, O_RDONLY);
	if (pars.fd == -1)
		return (err_fail("Error: No such file or directory\n"));
	pars.line = get_next_line(pars.fd);
	parser_map_while(cub, &pars);
	close(pars.fd);
}