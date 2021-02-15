/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 23:23:49 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		check_holes(char *str, int end)
{
	int i;

	i = 0;
	while (i < end)
	{
		if (str[i] == ' ')
		{
			if (i != 0 && str[i - 1] != '1')
				return (-1);
			while (str[i] == ' ')
				i++;
			if (str[i] != '1' && str[i - 1] != '1' && str[i - 1] != ' ')
				return (-1);
			if (str[i] != '1' && str[i] != '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}

char	*column_line(char *str, t_all *s, int i, int j)
{
	while (j < s->map.y && (s->map.tab[j][i] == '1'
		|| s->map.tab[j][i] == '0'
		|| s->map.tab[j][i] == ' ' || s->map.tab[j][i] == 'N'
		|| s->map.tab[j][i] == 'S' || s->map.tab[j][i] == 'W'
		|| s->map.tab[j][i] == 'E' || s->map.tab[j][i] == '2'))
	{
		str[j] = s->map.tab[j][i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int		check_columns(t_all *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (i < s->map.x - 1)
	{
		if (!(str = (char *)malloc(sizeof(char) * (s->map.y + 1))))
			return (-1);
		str = column_line(str, s, i, j);
		j = check_line(str);
		free(str);
		if (j < 0)
			return (-1);
		i++;
	}
	return (0);
}

int		check_line(char *str)
{
	int	i;
	int	k;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	if (str[i] != '1' && str[i] != '\0')
		return (-12);
	k = my_strlen(str) - 1;
	while (k > 0 && (str[k] == 32 || (int)str[k] < 0) && str[k] != '\0')
	{
		k--;
	}
	if (str[k] != '1' || (check_holes(&str[i], k + 1 - i) == -1))
		return (-12);
	return (0);
}

int		check_map_leaks(t_all *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		if (check_line(s->map.tab[j]) == -12)
			return (write_errors(s, -12));
		j++;
	}
	if (check_columns(s) == -1)
		return (write_errors(s, -12));
	j = 0;
	while (j < s->map.y)
	{
		if ((s->map.tab[j] = fill_map(s->map.tab[j], s->map.x)) == NULL)
			return (write_errors(s, -12));
		j++;
	}
	return (0);
}
