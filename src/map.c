#include <fcntl.h>
#include <stdio.h>

#include "libft.h"

char	**map_open(char *path)
{
	int	fd;
	char	*line;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("map");
		exit(1);
	}
	line = get_next_line(fd);
	if (line == NULL)
		exit(write(2, "Error: empty map file", 21));
}
