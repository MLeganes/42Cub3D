
#include "cub3d.h"

int	main(int argcnt, char **args)
{
	t_cub3d		cub;
	//char	**map;
	// char		arr[9][5] = {
	// 						{'1', '1', '1', '1', '1'} ,
	// 						{'1', '0', '0', '0', '1'} ,
	// 						{'1', '0', '1', '1', '1'} ,
	// 						{'1', '0', '1', '0', '0'} ,
	// 						{'1', '0', '1', '1', '1'} ,
	// 						{'1', '0', '0', '0', '1'} ,
	// 						{'1', '0', '0', '0', '1'} ,
	// 						{'1', '0', '0', '0', '1'} ,
	// 						{'1', '1', '1', '1', '1'}
	// 					};

	if (argcnt != 2)
	{
		write(2, "Error: Incorrect arguments!", 27);
		return (EXIT_FAILURE);
	}
	if (map_open(args[1], &cub))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// t_cor get_wall_pos(t_cor pos, t_cor dir, int** map)
// {
// 	// (pos.x / 1) + 1
// 	// if ()
// }
