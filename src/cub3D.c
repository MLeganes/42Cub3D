
#include "cub3d.h"

int	main(int argcnt, char **args)
{
	char	**map;
	char		arr[9][5] = {
							{'1', '1', '1', '1', '1'} ,
							{'1', '0', '0', '0', '1'} ,
							{'1', '0', '1', '1', '1'} ,
							{'1', '0', '1', '0', '0'} ,
							{'1', '0', '1', '1', '1'} ,
							{'1', '0', '0', '0', '1'} ,
							{'1', '0', '0', '0', '1'} ,
							{'1', '0', '0', '0', '1'} ,
							{'1', '1', '1', '1', '1'}
						};
	if (argcnt != 2)
		return (write(2, "Error: Incorrect arguments!", 27));
	map = map_open(args[1]);
	return (0);
}

t_cor get_wall_pos(t_cor pos, t_cor dir, int** map)
{
	(pos.x / 1) + 1
	if ()
}
