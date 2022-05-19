/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnies <mnies@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:27:49 by amorcill          #+#    #+#             */
/*   Updated: 2022/05/19 20:08:47 by mnies            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n'
			|| c == ' '))
		return (1);
	return (0);
}

static int	ft_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

/**
 * @brief	The ft_strtoi() function converts the string in str to a int value.
 * 			The string may begin with an arbitrary amount of white space (as
 * 			determined by ft_isspace) followed by a single optional `+' or `-'
 * 			sign. Base is taken as 10 (decimal) by default.
 *
 * @param str The sting with the number.
 * @param nbr Pointer to return the integer number.
 * @return int The ft_strtoi() function return the result of the conversion:
 * 	1 the conversion was successful.
 * 	0 is returned, if no conversion could be performed.
 */
int	ft_atoi_ext(const char *st, int *nbr)
{
	unsigned int	r;
	int				s;
	int				i;

	s = 1;
	r = 0;
	i = 0;
	while (ft_isspace(st[i]))
		i++;
	if (st[i] == '+' || st[i] == '-')
	{
		s = ft_sign(st[i]);
		i++;
	}
	while ((st[i] != '\n') && st[i] != '\0' && r <= 2147483648)
	{
		if (!ft_isdigit(st[i]))
			return (0);
		r = (r * 10) + (st[i] - '0');
		i++;
	}
	if ((s == -1 && r > 2147483648) || (s == 1 && r > INT_MAX) || st[0] == '\n')
		return (0);
	*nbr = (int)(s * r);
	return (1);
}
