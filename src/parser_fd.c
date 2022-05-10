#include "cub3d.h"

int parser_openfd(t_parser *pars, char *path)
{
	pars->fd = open(path, O_RDONLY);
	if (pars->fd == -1)
		return (err_fail("Error: No such file or directory\n"));
	return (EXIT_SUCCESS);
}

int parser_closefd(t_parser *pars)
{
	pars->fd = close(pars->fd);
	if (pars->fd == -1)
		return (err_fail("Error: Closing file descriptor\n"));
	return (EXIT_SUCCESS);
}

static int parser_readfdlines(t_parser *p, char *path)
{
	p->nolines = 0;
	if (parser_openfd(p, path))
		return (EXIT_FAILURE);
	p->line = get_next_line(p->fd);
	while (p->line)
	{
		p->nolines++;
		free(p->line);
		p->line = get_next_line(p->fd);
	}
	if (parser_closefd(p))
		return (EXIT_FAILURE);

	p->map = (char **)malloc(sizeof(char *) * (p->nolines + 1));
	if (p->map == NULL)
		return(err_fail("Error: problem in malloc\n"));
	return (EXIT_SUCCESS);
}

int parser_readfd(t_parser *p, char *path)
{
	if (parser_readfdlines(p, path))
		return (EXIT_FAILURE);

	if (parser_openfd(p, path))
		return (EXIT_FAILURE);

	p->line = get_next_line(p->fd);
	while (p->line)
	{
		p->map[p->idx] = p->line;
		p->idx++;
		p->map[p->idx] = NULL;
		p->line = NULL;
		p->line = get_next_line(p->fd);
	}
	p->map[p->idx] = NULL;
	//[possible]remove tabs by white-spaces

	if (parser_closefd(p))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
