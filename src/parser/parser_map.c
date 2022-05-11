#include "cub3d.h"

static int is_map_chars(char *line)
{
	if (*line == '\0')
		return (0);
	while(*line)
	{
		if (!is_space(*line) && !ft_strchr(MAP_CHARS, *line))
			return (0);
		line++; //line = line + sizeof(char);
	}
	return (1);
}

// Check horizontal 
static int is_map_wall(char *line)
{
	while (*line)
	{
		if (*line != '1' && !is_space(*line))
			return (0);
		line++;
	}
	return (1); //When all 1s, return 1.
}

static int is_player(t_parser *p)
{
	if (!p->player)
		return (0);
	return (1);
}

static int is_map_all_sides(char **map, int j)
{
	if (is_space(map[-1][j - 1]) || !map[-1][j - 1])
		return (0);
	if (is_space(map[-1][j]) || !map[-1][j])
		return (0);
	if (is_space(map[-1][j + 1]) || !map[-1][j + 1])
		return (0);
	if (is_space(map[0][j - 1]) || !map[0][j - 1])
		return (0);
	if (is_space(map[0][j + 1]) || !map[0][j + 1])
		return (0);
	if (is_space(map[1][j - 1]) || !map[1][j - 1])
		return (0);
	if (is_space(map[1][j]) || !map[1][j])
		return (0);
	if (is_space(map[1][j + 1]) || !map[1][j + 1])
		return (0);
	return (1);
}

static int is_map_closed(char **map)
{
	int j;

	j = 0;
	while (map[0][j])
	{
		/* code */
		if (ft_strchr(MAP_INSIDE, map[0][j]))
		{
			if (!is_map_all_sides(map, j))
				return (0);
		}
		j++;
	}
	return (1);
}

static int find_player(char *line, t_parser *p)
{
	while (*line)
	{
		if (ft_strchr(MAP_PLAYER, *line))
		{
			if (!p->player)
				p->player = *line;
			else
				return (0);
		}
		line++;
	}
	return (1);
}

static int is_valid_map(t_parser *p)
{
	int i;
	char **map;

	i = 0;
	map = &p->map[p->idx]; //copy pointer starting point map.
	while (is_map_chars(map[i]))
	{
		p->imap = i;
		if (i == 0 && !is_map_wall(map[i]))
			return (0);
		else if (!is_map_chars(map[i + 1]))
		{
			if ( i < 2)
				return (0);
			if (!is_player(p))
				return (0);
		}
		else //here working!!!!!
		{
			if (!is_map_closed(&map[i]) || !find_player(map[i], p))
				return (0);
		}
		i++;
	}
	// if (!copy_map(p))
	// 	return (0);
	return (1);
}

int	parser_map(t_cub3d *cub, t_parser *p)
{
	(void)cub;
	printf("\n\n **** PARSING MAP *****\n\n");

	remove_eol(p);
	p->idx = 0;
	//1
	while (p->map[p->idx] && !is_map_chars(p->map[p->idx]))
		p->idx++;
	//2
	if (!p->map[p->idx])
		return(err_fail("No map to parser in file cup\n"));
	//3
	if (!is_valid_map(p))
		return(err_fail("No valid map in .cup file\n"));
	
	//4
	while (p->map[p->idx] && is_map_chars(p->map[p->idx + 1]))
	{
		p->idx++;
	}
	return (EXIT_SUCCESS);
}