#include "cub3d.h"

static void free_cub3d_img(t_cub3d *cub)
{
	int i;

	i = 0;
	while (i < MAX)
	{
		if (cub->img[i])
		{
			if(cub->img[i]->path_tex)
			{
				mlx_destroy_image(cub->mlx, cub->img[i]->ptr);
				free(cub->img[i]->path_tex);
			}
			free(cub->img[i]);
		}
		i++;
	}
	return ;
}

static void free_cub3d_map(t_cub3d *cub)
{
	int i;

	i = 0;
	while (i < cub->map.nolines)
	{
		if (cub->map.map[i])
			free(cub->map.map[i]);
		i++;
	}
	if (cub->map.map)
		free(cub->map.map);
	mlx_destroy_window(cub->mlx, cub->win);

	printf("\n ******  This is the exit ********\n\n");
	system("leaks cub3d");

	return ;
}

int free_game(t_cub3d *cub)
{
	free_cub3d_img(cub);
	free_cub3d_map(cub);
	exit (EXIT_SUCCESS);
}

int exit_game(t_cub3d *cub)
{
	free_game(cub);
	return (EXIT_FAILURE);
}
