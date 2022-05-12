
#ifndef CUB3D_H
# define CUB3D_H

/***************************************************************************/
/* LIBC INCLUDES													   */
/***************************************************************************/
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "mlx.h"

/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */

# define MAX			4

# define MAX_COLOR		2
# define COLOR_NO_USED	-1
# define COLOR_IN_USE	0
# define MAP_CHARS "01NSEW"
# define MAP_INSIDE "0NSEW"
# define MAP_PLAYER "NSEW"

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
 * 			COLOR_NO_USED	-1
 *			COLOR_IN_USE	0
 *
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
	double	x;
	double	y;
}			t_cor;

typedef struct s_cub3d{
	char	*img_no;
	char	*img_so;
	char	*img_we;
	char	*img_ea;
	t_img	*img[MAX];
	t_color color[MAX_COLOR];	//Color for floor and celling.
	int		color_floor; //no used
	int		color_celling; //no used
	t_map	map;

}			t_cub3d;

typedef struct s_parser_helper
{
	int				fd;
	char			*line;
	char			**split;
	int				idx;
	int				nolines;
	int				imap;
	char			**map;
	char			player;
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
void	parser_init(t_parser *pars);
int		parser_readfd(t_parser *p, char *path);
int		parser_identifier(t_cub3d *cub, t_parser *p);
int		identifier_color(t_cub3d *cub, t_parser *p, char c);
int		parser_map(t_cub3d *cub, t_parser *p);
char	*ident2str(t_identifier ident);

/*
 * PARSER UTILS
 */
int		is_ext_cub(char *path);
int		is_ext_xpm(t_parser *p);
int		is_space(char c);
int		is_path(char *path);
void	remove_eol(t_parser *p);

/*
 * ERROR
 */
int		err_fail(char *msg);
int		err_fail2(char *msg1, char *msg2);

/*
 * FRAME
 */
void	test_frame(t_cub3d *cub);

#endif
