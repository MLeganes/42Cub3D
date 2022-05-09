#include "cub3d.h"

int err_fail(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}
