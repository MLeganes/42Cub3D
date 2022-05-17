
#ifndef CUB3D_H
# define CUB3D_H

/***************************************************************************/
/* LIBC INCLUDES													   */
/***************************************************************************/
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

/* ************************************************************************** */
/* DEFINE CONSTANS														  	  */
/* ************************************************************************** */

# define MAX			4
# define MAX_COLOR		2
# define W_HEIGHT		500
# define W_WIDTH		1000
# define COLOR_NO_USED	-1
# define COLOR_IN_USE	0
# define MAP_CHARS "01NSEW"
# define MAP_INSIDE "0NSEW"
# define MAP_PLAYER "NSEW"


/*
 * KEY CODES
 */
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

/* ************************************************************************** */
/* STRUCT DEFS															  	  */
/* ************************************************************************** */
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
	int		nolines;
	char	**map;
}			t_map;

typedef struct s_cor{
	float	x;
	float	y;
}			t_cor;

typedef struct s_cub3d{
	char	*img_no;//no used
	char	*img_so;//no used
	char	*img_we;//no used
	char	*img_ea;//no used
	t_img	*img[MAX];
	t_color color[MAX_COLOR];	//Color for floor and celling.
	int		color_floor;
	int		color_celling;
	t_map	map;
	t_cor	pos;
	int		rotation;
	void	*win;
	void	*mlx;

}			t_cub3d;

typedef struct s_parser_helper
{
	int				fd;
	char			*line;
	char			**split;
	char			**map;
	int				idx;
	int				imap;
	int				nolines;
	char			player;
	t_cor			player_pos;
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
void	free_split(t_parser *p);

/*
 * PARSER UTILS
 */
int		is_ext_cub(char *path);
int		is_ext_xpm(t_parser *p);
int		is_space(char c);
int		is_path(char *path);
void	remove_eol(t_parser *p);
int		is_map_all_sides(char **map, int j);
int		is_player(t_parser *p);
int		is_map_wall(char *line);
int		is_map_chars(char *line);


/*
 * FRAME
 */
int		render_frame(void *cub_ptr);

/*
 * FREE
 */
void	free_cub3d(t_cub3d *c);

/*
 * GAME
 */

int game(t_cub3d *cub);

/*
 * ERROR
 */
int		err_fail(char *msg);
int		err_fail2(char *msg1, char *msg2);

#endif
