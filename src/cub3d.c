#include "cub3d.h"

void cub3d_init(t_cub3d *cub)
{

	cub->img_ea = NULL;
	cub->img[ID_NO] = malloc(sizeof(t_img));
	cub->img[ID_SO] = malloc(sizeof(t_img));
	cub->img[ID_WE] = malloc(sizeof(t_img));
	cub->img[ID_EA] = malloc(sizeof(t_img));

	cub->img[ID_NO]->path_tex = NULL;
	cub->img[ID_SO]->path_tex = NULL;
	cub->img[ID_WE]->path_tex = NULL;
	cub->img[ID_EA]->path_tex = NULL;

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

	// PLAYER
	cub->rotation = -1;
	cub->pos.x = -1;
	cub->pos.y = -1;
}

void cub3d_init_afterparser(t_cub3d *cub)
{
	// MAP
	cub->map.rows = map_count_lines(cub->map.map);
	cub->map.cols = map_max_strlen(cub->map.map);
	cub->map.tile_size = calculate_tilesize(cub);
	cub->map.h = cub->map.rows * cub->map.tile_size;
	cub->map.w = cub->map.cols * cub->map.tile_size;

	// MLX 
	cub->img3d = malloc(sizeof(t_img));
	cub->win_h = W_HEIGHT; // 480
	cub->win_w = W_WIDTH; // 640;
}

int	main(int argcnt, char **args)
{
	t_cub3d	cub;

	if (argcnt != 2)
		exit (err_fail("Incorrect arguments!\n"));

	cub3d_init(&cub);

	if (parser(args[1], &cub))
		exit (err_fail("Main-Parser fail\n"));

	cub3d_init_afterparser(&cub);

	game(&cub);
	free_cub3d(&cub);

	system("leaks cub3d");

	exit (EXIT_SUCCESS);
}
