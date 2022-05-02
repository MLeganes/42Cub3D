
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

# define MAX	4

typedef enum e_identifier
{
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_F,
	ID_C,
}	t_identifier;

typedef struct s_img
{
	char	*path_tex;
	void	*ptr; //mlx pointer
}				t_img;

typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
}			t_map;

typedef struct s_cor{
	int		x;
	int		y;
}				t_cor;

typedef struct s_cub3d{
	char	*img_no;
	char	*img_so;
	char	*img_we;
	char	*img_ea;

	// no idea with one to use!!!
	t_img	*img[MAX];
	char	*img_path_tex[MAX];
	
	int		color_floor;
	int		color_celling;
	t_map	map;
}				t_cub3d;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * CUB3D
 */




/*
 * MAP
 */
int	map_init(char *path, t_cub3d *cub);
int	map_get_imgs_path(t_cub3d *cub, char *path);
int	map_find_identifier(t_cub3d *cub, t_identifier ident, char *cub_map);

/*
 * ERROR
 */
int error_exit_failure(char *msg);

#endif