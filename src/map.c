
#include "cub3d.h"


int	map_open(char *path, t_cub3d *cub)
{
	int		fd;
	char	*line;

	// To avoid error massage.
	cub->floor_color = 1;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1 || ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4))
	{
		perror("map");
		exit(write(2, "Error: map file no valid path or wrong extension", 21));
	}
	line = get_next_line(fd);
	if (line == NULL)
		exit(write(2, "Error: empty map file", 21));

	return (EXIT_SUCCESS);
}
