
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
}			t_img;

typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
}			t_map;

typedef struct s_cor{
	int		x;
	int		y;
}			t_cor;

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

}			t_cub3d;

/********
 * 
 * t_parser helper struct used in parser_texture.c
 * due to the 25 lines 
 * 
 * status:
 * 				INIT_STATE		-1	// Starting point
 * 				EXIT_SUCESS		0
 * 				EXIT_FAILURE	1
 * 				ERROR			2
 */
typedef struct s_parser_helper
{
	int				fd;
	int				status;
	t_identifier	ident;
	char			*line;
	char			*start_line;
}					t_parser;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

/*
 * CUB3D
 */

/*
 * PARSER
 */
int		parser(char *path, t_cub3d *cub);
void	parser_init(t_parser *pars, t_identifier ident);
int		parser_texture(t_cub3d *cub, char *path_cub);

/*
 * VALIDATION
 */
int		is_ext_xpm(t_parser *p);

/*
 * ERROR
 */
int		error_exit_failure(char *msg);

#endif
