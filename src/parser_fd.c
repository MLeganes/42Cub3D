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

static int map_add_line(t_parser **p)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * ( (*p)->nolines + 2));
	if (tmp == NULL)
		return (EXIT_FAILURE);
	i = 0;
	if((*p)->map == NULL)
	{
		tmp[0] = ft_strdup((*p)->line);
		tmp[1] = NULL;
	}
	else
	{
		while((*p)->map[i])
		{
			printf("While %d  %s\n",i ,(*p)->map[i]);
			tmp[i] = (*p)->map[i];
			i++;
		}
		tmp[i] = ft_strdup((*p)->line);
		tmp[i++] = NULL;
		free((*p)->map);
	}
	(*p)->map = tmp;
	(*p)->nolines++;	
	return (EXIT_SUCCESS);
}

int parser_readfd(t_parser *p)
{
	p->line = get_next_line(p->fd);
	while (p->line)
	{
		if (map_add_line(&p))
			return (EXIT_FAILURE);
		free(p->line);
		p->line = get_next_line(p->fd);
	}
	//[possible]remove tabs by white-spaces
	return (EXIT_SUCCESS);
}
