
#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_map{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int		floor_color;
	int		celling_color;
	char	**map;
}				t_map;

typedef struct s_cor{
	int		x;
	int		y;
}				t_cor;

#endif