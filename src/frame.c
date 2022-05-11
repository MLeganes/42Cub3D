#include "cub3d.h"

void	test_frame(void)
{
	void	*win;
	void	*mlx;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 500, "test");
	mlx_pixel_put(mlx, win, 10, 10, 242);
	mlx_loop(mlx);
}
