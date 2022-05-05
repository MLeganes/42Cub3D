#include "cub3d.h"

int error_exit_failure(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}
