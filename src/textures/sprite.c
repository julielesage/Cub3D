/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 23:07:15 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

unsigned int	pixelize_spr(t_all *s, int index, unsigned int color)
{
	if (color == 0)
		return (s->img.adr[index]);
	return (color);
}

void			draw_sprite(t_all *s, int loc, double dist)
{
	int				index;
	int				i;
	int				j;
	unsigned int	color;
	double			size;

	i = 0;
	j = 0;
	size = s->win.y / dist / 2;
	loc = loc - size / 2;
	while (i < size)
	{
		while ((loc + i >= 0 && loc + i < s->win.x) &&
		(j < size && s->stock[loc + i].dis > dist))
		{
			color = 64 * floor(64 * (double)j / size) + (double)i / size * 64;
			color = s->texspr.adr[color];
			index = loc + i + (s->win.y / 2 + j) * s->win.x;
			if (index < s->win.x * s->win.y)
				s->img.adr[index] = pixelize_spr(s, index, color);
			j++;
		}
		i++;
		j = 0;
	}
}

void			locate_spr(t_all *s, double spx, double spy, double spdis)
{
	double	angle;

	spx = (spx - s->pos.x) / spdis;
	spy = (spy - s->pos.y) / spdis;
	if (spy <= 0)
		angle = acos(spx) * 180 / M_PI;
	else
		angle = 360 - acos(spx) * 180 / M_PI;
	angle = s->dir.angle - angle + 33;
	if (angle >= 180)
		angle -= 360;
	else if (angle <= -180)
		angle += 360;
	draw_sprite(s, angle * s->win.x / 66, spdis);
}

void			unsort_sprite(t_all *s)
{
	t_spr	temp;
	int		i;
	int		j;

	i = 0;
	while (i < s->map.nbspr - 1)
	{
		j = i + 1;
		while (j < s->map.nbspr)
		{
			if (s->sprite[i].dis < s->sprite[j].dis)
			{
				temp = s->sprite[i];
				s->sprite[i] = s->sprite[j];
				s->sprite[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void			handle_sprite(t_all *s)
{
	int			i;
	double		distance;

	distance = hypot(s->dir.x, s->dir.y);
	if (s->dir.y <= 0)
		s->dir.angle = acos(s->dir.x / distance) * 180 / M_PI;
	else
		s->dir.angle = 360 - acos(s->dir.x / distance) * 180 / M_PI;
	i = 0;
	while (i < s->map.nbspr)
	{
		s->sprite[i].dis = hypot(s->sprite[i].x - s->pos.x,
		s->sprite[i].y - s->pos.y);
		i++;
	}
	unsort_sprite(s);
	i = 0;
	while (i < s->map.nbspr)
	{
		locate_spr(s, s->sprite[i].x, s->sprite[i].y, s->sprite[i].dis);
		i++;
	}
	free(s->stock);
}
