#include "cub3d.h"

int	is_map_chars(char *line)
{
	if (line == NULL || *line == '\0')
		return (0);
	while (*line)
	{
		if (!is_space(*line) && !ft_strchr(MAP_CHARS, *line))
			return (0);
		line++;
	}
	return (1);
}

int	is_map_wall(char *line)
{
	while (*line)
	{
		if (*line != '1' && !is_space(*line))
			return (0);
		line++;
	}
	return (1);
}

int	is_player(t_parser *p)
{
	if (!p->player)
		return (0);
	return (1);
}

int	is_map_all_sides(char **map, int j)
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

