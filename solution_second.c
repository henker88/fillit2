/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_second.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgendry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:54:15 by sgendry           #+#    #+#             */
/*   Updated: 2018/12/27 14:23:23 by sgendry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				zero_map(int size, unsigned char tab[size][size])
{
	int				i;
	int				j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			tab[i][j] = 0;
			j++;
		}
		i++;
	}
}

int					help_rec(int size, unsigned char tab[size][size],
					t_tetra *tetra, int *flag)
{
	unsigned char	cpy[size][size];

	if (check_figure(size, tab) && !(tetra->next))
	{
		print_map(size, tab);
		*flag = 1;
		return (1);
	}
	if (!check_figure(size, tab))
		remove_figure(size, tab, tetra);
	else if (check_figure(size, tab) && tetra->next)
	{
		cpy_arr(size, tab, cpy);
		if (!(rec(size, cpy, tetra->next, flag)))
		{
			remove_figure(size, tab, tetra);
		}
	}
	return (0);
}

int					rec(int size, unsigned char tab[size][size], t_tetra *tetra,
					int *flag)
{
	int				i;
	int				j;
	int				coordinates[2];

	i = -1;
	while (++i < (size - (tetra->p[1] - tetra->p[0])))
	{
		j = -1;
		while (++j < (size - (tetra->p[3] - tetra->p[2])))
		{
			if (*flag == 1)
				return (1);
			if (i == 0 && j == 0 && tetra->symb == 'A')
				zero_map(size, tab);
			coordinates[0] = i;
			coordinates[1] = j;
			put_figure(size, tab, tetra, coordinates);
			if (help_rec(size, tab, tetra, flag))
				return (1);
		}
	}
	if (tetra->symb == 'A')
		rec(size + 1, tab, tetra, flag);
	return (0);
}

int					solut(t_tetra *tetra)
{
	int				size;
	unsigned char	s[2][2];
	int				i;
	int				j;
	int				flag;

	i = 0;
	size = 2;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			s[i][j] = 0;
			j++;
		}
		i++;
	}
	flag = 0;
	i = rec(size, s, tetra, &flag);
	return (1);
}
