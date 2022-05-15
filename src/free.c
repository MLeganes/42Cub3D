#include "cub3d.h"

void free_cub3d(t_cub3d *cub)
{

	free(cub->img[ID_NO]);
	free(cub->img[ID_SO]);
	free(cub->img[ID_WE]);
	free(cub->img[ID_EA]);

	// int i;

	// i = 0;
	// while (i < 4 && c->img[i])
	// {
	// 	free(c->img[i]->path_tex);
	// 	c->img[i]->path_tex = NULL;
	// 	//free(c->img[i]->ptr);
	// 	//c->img[i]->ptr = NULL;
	// 	free(c->img[i]);
	// 	c->img[i] = NULL;
	// 	i++;
	// }
}
