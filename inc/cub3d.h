
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

# define W_HEIGHT		1000
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
	void	*ptr;
	int		*addr;
	int		bits_p_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
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
	int		h;
	int		w;
	int		rows;
	int		cols;
	int		tile_size;
	int		nolines; // it should be same as rows
	char	**map;
}			t_map;

typedef struct s_cor{
	float	x;
	float	y;
}			t_cor;


typedef struct	s_ray
{
	double		fov;
	double		fovref_min;
	double		fovref_max;
	double		wall_strip_w;
	int			num_rays;
	double		distprojplane;
	double		ray_angle;
	int			facing_down;
	int			facing_left;
	double		horxstep;
	double		horystep;
	double		verxstep;
	double		verystep;
	double		wall_hit_horx;
	double		wall_hit_hory;
	double		wall_hit_verx;
	double		wall_hit_very;
	double		wall_hit_x;
	double		wall_hit_y;
	int			found_hor_wall;
	int			found_ver_wall;
	double		distance;
	int			hit_vertical;
}				t_ray;


typedef struct s_cub3d
{
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	t_img	*img[MAX];
	t_color	color[MAX_COLOR];
	int		color_floor;
	int		color_celling;
	t_img	*img3d;
	t_map	map;
	t_cor	pos;
	int		rotation;

}			t_cub3d;

typedef struct s_draw{
	t_cub3d	*cub;
	t_cor	*poscntct;
}			t_draw;

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
 * CONTACT
 */
void	contact_get_next(t_cor *pos, t_cor *vec);
int		contact_is_wall(t_cub3d *cub, t_cor *pos_cntct, t_cor *vec);

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
void	get_next_contact_point(t_cor *pos, t_cor *vec);
int		is_wall(t_cub3d *cub, t_cor *pos_cntct, t_cor *vec);

/*
 * FREE
 */
void	free_cub3d(t_cub3d *c);

/*
 * GAME
 */
int		game(t_cub3d *cub);
int		game_key_hooks(t_cub3d *cub);

/*
 * GAME UTILS
 */
int		map_count_lines(char **strs);
int		map_max_strlen(char **strs);
double	calculate_tilesize(t_cub3d *cub);


/*
 * ERROR
 */
int		err_fail(char *msg);
int		err_fail2(char *msg1, char *msg2);

#endif
