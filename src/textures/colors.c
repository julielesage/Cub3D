/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 23:05:11 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

unsigned int	color_pixel(t_all *s, double i)
{
	int	index;

	if (floor(s->hit.y) == s->hit.y)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.x - floor(s->hit.x));
		if (s->ray.hor == 1)
			return (s->texsouth.adr[index]);
		else if (s->ray.hor == 0)
			return (s->texnorth.adr[index]);
	}
	else if (floor(s->hit.x) == s->hit.x)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.y - floor(s->hit.y));
		if (s->ray.ver == 1)
			return (s->texeast.adr[index]);
		else if (s->ray.ver == 0)
			return (s->texwest.adr[index]);
	}
	return (0x00000000);
}

void			color_column(t_all *s, int size)
{
	unsigned int	color;
	int				start;
	int				count;

	start = s->win.x * (s->win.y - size) / 2;
	if (size > s->win.y)
		count = (size - s->win.y) / 2;
	else
		count = 0;
	color = s->ceil;
	while (s->ray.i < s->win.x * s->win.y)
	{
		if (s->ray.i >= start && count < size)
		{
			color = color_pixel(s, (double)count / size);
			count++;
		}
		else if (count == size)
			color = s->floor;
		s->img.adr[s->ray.i] = mlx_get_color_value(s->mlx.ptr, color);
		s->ray.i += s->win.x;
	}
	s->ray.i -= s->win.x * s->win.y;
}

int				get_color(unsigned int *addr, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*addr != NONE)
		return (-5);
	(*i)++;
	r = my_atoi(line, i);
	(*i)++;
	g = my_atoi(line, i);
	(*i)++;
	b = my_atoi(line, i);
	skip_spaces(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-6);
	*addr = r * 65536 + g * 256 + b;
	return (0);
}
