#include "cub3d.h"

static int	is_map_closed(char **map)
{
	int	j;

	j = 0;
	while (map[0][j])
	{
		if (ft_strchr(MAP_INSIDE, map[0][j]))
		{
			if (!is_map_all_sides(map, j))
				return (0);
		}
		j++;
	}
	return (1);
}

static int	find_player(char *line, t_parser *p)
{
	while (*line)
	{
		if (ft_strchr(MAP_PLAYER, *line))
		{
			if (p->player == '\0')
				p->player = *line;
			else
				return (0);
		}
		line++;
	}
	return (1);
}

int	copy_map_to_cub(t_cub3d *cub, t_parser *parse, char **map)
{
	int	i;

	i = 0;
	cub->map.height = 0;
	cub->map.width = 0;
	cub->map.map = (char **)malloc(sizeof(char *) * (parse->nolines + 2));
	while (map[i])
	{
		cub->map.map[i] = ft_strdup(map[i]);
		i++;
	}
	cub->map.map[i] = NULL;
	cub->player = parse->player;
	return (1);
}

static int	is_valid_map(t_parser *p, t_cub3d *cub, char **map, int i)
{
	while (map[i] && is_map_chars(map[i]))
	{
		p->imap = i;
		if (i == 0 && !is_map_wall(map[i]))
			return (0);
		else if (map[i] && !is_map_chars(map[i + 1]))
		{
			if (i < 2)
				return (0);
			if (!is_player(p))
				return (0);
		}
		else
		{
			if (!is_map_closed(&map[i]) || !find_player(map[i], p))
				return (0);
		}
		i++;
	}
	if (!is_map_wall(map[i - 1]) && is_map_closed(&map[i - 2]))
		return (0);
	if (!copy_map_to_cub(cub, p, map))
		return (0);
	return (1);
}

int	parser_map(t_cub3d *cub, t_parser *p)
{
	int		i;
	char	**fucking25lines_map;

	printf("\n\n **** PARSING MAP *****\n\n");
	remove_eol(p);
	p->idx = 0;
	while (p->map[p->idx] && !is_map_chars(p->map[p->idx]))
		p->idx++;
	if (!p->map[p->idx])
		return (err_fail("No map to parser in file cup\n"));
	i = 0;
	fucking25lines_map = &p->map[p->idx];
	if (!is_valid_map(p, cub, fucking25lines_map, i))
		return (err_fail("No valid map in .cup file\n"));
	return (EXIT_SUCCESS);
}
