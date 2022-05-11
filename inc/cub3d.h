
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

# define MAX			4

# define MAX_COLOR		2
# define COLOR_NO_USED	-1
# define COLOR_IN_USE	0

typedef enum e_identifier
{
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_MAP,
	ID_NONE,
}	t_identifier;

typedef enum e_identifier_color
{
	ID_F,
	ID_C,
}	t_identcolor;

typedef struct s_img
{
	char	*path_tex;
	void	*ptr; //mlx pointer
}			t_img;

/********
 * t_color
 * 
 * used:
 * 			NO_USED	-1
 * 			IN_USE	0
 */
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		rgb;
	int		used;
}			t_color;

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
	//char	*img_path_tex[MAX];

	t_color color[MAX_COLOR];	//Color for floor and celling.
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
 * 				INIT_STATE		-1	// Starting point. 
 * 				SUCESS			0
 * 				ERROR			2
 * 				ERROR			3
 */
typedef struct s_parser_helper
{
	int				fd;
	char			*line;
	char			**split;
	int				idx;
	int				nolines;
	char			**map;
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
//new functions
int		parser(char *path, t_cub3d *cub);
void	parser_init(t_parser *pars);
int		parser_readfd(t_parser *p, char *path);
int		parser_identifier(t_cub3d *cub, t_parser *p);
int		identifier_color(t_cub3d *cub, t_parser *p, char c);
int	parser_map(t_cub3d *cub, t_parser *p, char *path_cub);

char	*ident2str(t_identifier ident);

//old functions
//int		parser_color(t_cub3d *cub, char *path_cub);

/*
 * UTILS
 */
int		is_ext_cub(char *path);
int		is_ext_xpm(t_parser *p);
int		rgb_to_colorHex(int r, int g, int b);

/*
 * ERROR
 */
int		err_fail(char *msg);
int		err_fail2(char *msg1, char *msg2);

#endif
