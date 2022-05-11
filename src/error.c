#include "cub3d.h"

int err_fail(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}

int err_fail2(char *msg1, char *msg2)
{
	write(2, "Error\n", 6);
	write(2, msg1, ft_strlen(msg1));
	write(2, msg2, ft_strlen(msg2));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}
