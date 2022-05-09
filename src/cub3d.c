#include "cub3d.h"

void cub3d_init(t_cub3d *cub)
{
	cub->img_ea = NULL;
	cub->img[ID_NO] = malloc(sizeof(t_img));
	cub->img[ID_SO] = malloc(sizeof(t_img));
	cub->img[ID_WE] = malloc(sizeof(t_img)); 
	cub->img[ID_EA] = malloc(sizeof(t_img)); 

	cub->color[ID_C].r = -1; 
	cub->color[ID_C].g = -1; 
	cub->color[ID_C].b = -1; 
	cub->color[ID_C].rgb = -1;
	cub->color[ID_C].used = COLOR_NO_USED;

	cub->color[ID_F].r = -1; 
	cub->color[ID_F].g = -1; 
	cub->color[ID_F].b = -1; 
	cub->color[ID_F].rgb = -1; 
	cub->color[ID_F].used = COLOR_NO_USED; 
}

int	main(int argcnt, char **args)
{
	t_cub3d	cub;

	if (argcnt != 2)
		exit (err_fail("Error: Incorrect arguments!\n"));
	
	cub3d_init(&cub);

	if (parser(args[1], &cub))
		exit (EXIT_FAILURE);

	system("leaks cub3d");
	exit (EXIT_SUCCESS);
}
