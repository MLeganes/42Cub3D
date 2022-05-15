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
	// free(cub->img[ID_NO]->path_tex);
	// free(cub->img[ID_NO]);
	// free(cub->img[ID_SO]->path_tex);
	// free(cub->img[ID_SO]);
	// free(cub->img[ID_WE]->path_tex);
	// free(cub->img[ID_WE]);
	// free(cub->img[ID_EA]->path_tex);
	// free(cub->img[ID_EA]);

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
