#include "cub3d.h"

t_cor	get_next_contact_point(t_cor pos, t_cor vec);

void	test_frame(t_cub3d *cub)
{
	void	*win;
	void	*mlx;
	t_cor	pos;
	t_cor	vec;


	(void)cub;


	pos.x = 0;
	pos.y = 0;
	vec.x = 10;
	vec.y = -4;
	while (pos.x < 100 && pos.y < 100 && pos.x > -100 && pos.y > -100)
		pos = get_next_contact_point(pos, vec);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 500, "test");
	mlx_pixel_put(mlx, win, 10, 10, 242);
	mlx_loop(mlx);
}

t_cor	get_next_contact_point(t_cor pos, t_cor vec)
{
	double	mx;
	double	my;
	int		stepx;
	int		stepy;

	stepx = 1;
	if (vec.x < 0)
		stepx = -1;
	stepy = 1;
	if (vec.y < 0)
		stepy = -1;
	if (vec.y != 0 && vec.x != 0)
	{
		my = (stepy - (pos.y - (long)pos.y)) / vec.y;
		mx = (stepx - (pos.x - (long)pos.x)) / vec.x;
	}
	if (vec.y != 0 && vec.x != 0 && my > mx)
		pos.y = pos.y + vec.y * mx;
	else if (vec.y != 0)
		pos.y = (long)(pos.y + stepy);
	if (vec.x != 0 && vec.y != 0 && my < mx)
		pos.x = pos.x + vec.x * my;
	else if (vec.x != 0)
		pos.x = (long)(pos.x + stepx);
	return (pos);
}
