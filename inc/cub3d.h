
#ifndef CUB3D_H
# define CUB3D_H


/***************************************************************************/
/* LIBC INCLUDES													   */
/***************************************************************************/
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"


/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */
typedef struct s_cub3d{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int		floor_color;
	int		celling_color;
	char	**map;
}				t_cub3d;

typedef struct s_cor{
	int		x;
	int		y;
}				t_cor;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * CUB3D
 */



/*
 * MAP
 */
int	map_open(char *path, t_cub3d *cub);

#endif




