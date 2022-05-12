#include "cub3d.h"

static char	*identcolor2str(t_identcolor ident)
{
	if (ident == ID_C)
		return ("C");
	if (ident == ID_F)
		return ("F");
	return (NULL);
}

static int	rgb_to_color_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

static int	get_rgb_colornumber(t_cub3d *cub, t_parser *p, int i,
		t_identcolor id)
{
	int	nbr;

	if (ft_atoi_ext(p->split[i], &nbr))
	{
		if ((nbr < 0) || (nbr > 255))
			return (err_fail2("RGB color smaller than 0 or bigger than 255 in ",
					identcolor2str(id)));
		else if (i == 0)
			cub->color[id].r = nbr;
		else if (i == 1)
			cub->color[id].g = nbr;
		else if (i == 2)
			cub->color[id].b = nbr;
		return (EXIT_SUCCESS);
	}
	else
		return (err_fail2("RGB color is not digit in ", identcolor2str(id)));
}

static int	get_rgb(t_cub3d *cub, t_parser *p, t_identcolor id)
{
	int	i;

	if ((!p->line) || (ft_strlen(p->line) < 6) || (p->line[0] == '\n'))
		return (err_fail2("Something missing in RGB colors in ",
				identcolor2str(id)));
	p->split = ft_split(p->line, ',');
	i = 0;
	while (i < 3)
	{
		if (!p->split[i])
			return (err_fail2("Missing RGB color in the ", identcolor2str(id)));
		if (get_rgb_colornumber(cub, p, i, id))
			return (EXIT_FAILURE);
		i++;
	}
	if (i == 3)
	{
		cub->color[id].rgb = rgb_to_color_hex(cub->color[id].r,
				cub->color[id].g, cub->color[id].b);
		printf("Color rgb: %d in the %s \n", cub->color[id].rgb,
			identcolor2str(id));
		cub->color[id].used = COLOR_IN_USE;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	identifier_color(t_cub3d *cub, t_parser *p, char c)
{
	printf("\nIDENTIFIER COLOR: %c ", c);
	p->line = p->map[p->idx];
	p->line++;
	while (p->line && *(p->line) && ft_strchr(" \t\r", *(p->line)))
		p->line++;
	if (c == 'C')
	{
		printf("color C found: %s\n", p->line);
		if (cub->color[ID_C].used == COLOR_NO_USED)
			return (get_rgb(cub, p, ID_C));
		else
			return (err_fail2("Color is repited in the map ", p->map[p->idx]));
	}
	if (c == 'F')
	{
		printf("color F found: %s\n", p->line);
		if (cub->color[ID_F].used == COLOR_NO_USED)
			return (get_rgb(cub, p, ID_F));
		else
			return (err_fail2("Color is repited in the map ", p->map[p->idx]));
	}
	return (EXIT_SUCCESS);
}
