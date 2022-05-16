#include "cub3d.h"

void free_cub3d(t_cub3d *cub)
{
	int i;

	// free img
	i = 0;
	while (i < MAX)
	{
		if (cub->img[i])
		{
			if(cub->img[i]->path_tex)
				free(cub->img[i]->path_tex);
			free(cub->img[i]);
		}
		i++;
	}
	i = 0;
	while (i < cub->map.nolines)
	{
		if (cub->map.map[i])
			free(cub->map.map[i]);
		i++;
	}
	if (cub->map.map)
		free(cub->map.map);
}
