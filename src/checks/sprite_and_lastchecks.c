/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_and_lastchecks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 23:25:50 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		parse_sprite(t_all *s)
{
	int	i;
	int	j;
	int	k;

	if (s->sprite)
		s->sprite = NULL;
	if (!(s->sprite = malloc(sizeof(t_spr) * s->map.nbspr)))
		return (-1);
	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		k = 0;
		while (k < s->map.x)
		{
			if (s->map.tab[j][k] == '2')
			{
				s->sprite[i].y = (double)j + 0.5;
				s->sprite[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}

int		last_checks(t_all *s)
{
	if (s->error.map < 0)
		return (-1);
	else if (s->win.x <= 0 || s->win.y <= 0)
		return (write_errors(s, -14));
	else if (!s->texnorth.adr || !s->texsouth.adr || !s->texeast.adr
		|| !s->texwest.adr || !s->texspr.adr)
		return (write_errors(s, -15));
	else if (s->ceil == NONE || s->floor == NONE)
		return (write_errors(s, -16));
	else if (s->error.pos == 0)
		return (write_errors(s, -17));
	else if (s->error.pos > 1)
		return (write_errors(s, -18));
	return (1);
}

char	*fill_map(char *str, int len)
{
	int		i;
	char	*filled_str;

	i = 0;
	if (!(filled_str = malloc(sizeof(char) * (len))))
		return (NULL);
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == ' ')
			filled_str[i] = '1';
		else
			filled_str[i] = str[i];
		i++;
	}
	while (i < len)
	{
		filled_str[i] = '1';
		i++;
	}
	filled_str[len] = '\0';
	free(str);
	return (filled_str);
}
