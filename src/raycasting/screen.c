/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 22:14:28 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	is_horizontal(t_all *s)
{
	double	y;
	double	x;

	y = floor(s->pos.y) + s->ray.hor;
	x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < s->map.x)
	{
		if (s->map.tab[(int)(y - 1 + s->ray.hor)][(int)floor(x)] == '1')
		{
			if (s->hit.distance > hypot(x - s->pos.x, y - s->pos.y))
			{
				s->hit.x = x;
				s->hit.y = y;
				s->hit.distance = hypot(x - s->pos.x, y - s->pos.y);
			}
			return ;
		}
		y += (2 * s->ray.hor - 1);
		x += (2 * s->ray.hor - 1) * s->ray.x / s->ray.y;
	}
}

void	is_vertical(t_all *s)
{
	double	x;
	double	y;

	x = floor(s->pos.x) + s->ray.ver;
	y = s->pos.y + (x - s->pos.x) * (s->ray.y / s->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
	{
		if (s->map.tab[(int)floor(y)][(int)(x - 1 + s->ray.ver)] == '1')
		{
			s->hit.x = x;
			s->hit.y = y;
			s->hit.distance = hypot(x - s->pos.x, y - s->pos.y);
			return ;
		}
		x += (2 * s->ray.ver - 1);
		y += (2 * s->ray.ver - 1) * s->ray.y / s->ray.x;
	}
	s->hit.x = s->pos.x;
	s->hit.y = s->pos.y;
	s->hit.distance = 1000000000;
}

void	is_direction(t_all *s)
{
	if (s->ray.x >= 0)
		s->ray.ver = 1;
	else
		s->ray.ver = 0;
	if (s->ray.y >= 0)
		s->ray.hor = 1;
	else
		s->ray.hor = 0;
}

void	is_ray(t_all *s)
{
	double	angle;
	double	distance;

	angle = ((double)s->ray.i - (s->win.x / 2)) * 33 / (s->win.x / 2);
	angle = angle * M_PI / 180;
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
	distance = hypot(s->ray.x, s->ray.y);
	s->ray.x /= distance;
	s->ray.y /= distance;
}

void	build_screen(t_all *s)
{
	int bpp;
	int sl;
	int end;

	if (s->img.ptr)
	{
		mlx_destroy_image(s->mlx.ptr, s->img.ptr);
		s->img.ptr = NULL;
	}
	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &sl, &end);
	s->stock = malloc(sizeof(t_stk) * s->win.x);
	while (s->ray.i < s->win.x)
	{
		is_ray(s);
		is_direction(s);
		is_vertical(s);
		is_horizontal(s);
		register_ray(s);
		color_column(s, size_col(s));
		s->ray.i++;
	}
	handle_sprite(s);
}
