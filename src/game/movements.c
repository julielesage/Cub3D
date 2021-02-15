/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 21:24:55 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		game_loop(t_all *s)
{
	if (s->pos.fwd == 1)
		moving(s, 1);
	else if (s->pos.bwd == 1)
		moving(s, -1);
	else if (s->pos.rotleft == 1)
		rotation(s, -1);
	else if (s->pos.rotright == 1)
		rotation(s, 1);
	else if (s->pos.right == 1)
		sidesteping(s, 1);
	else if (s->pos.left == 1)
		sidesteping(s, -1);
	play(s);
	return (1);
}

void	play(t_all *s)
{
	t_ray	ray;
	t_hit	hit;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.ver = 0;
	ray.hor = 0;
	hit.x = 0;
	hit.y = 0;
	hit.distance = 0;
	s->ray = ray;
	s->hit = hit;
	build_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
}

void	sidesteping(t_all *s, double c)
{
	s->pos.x -= c * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.x += c * (s->dir.y * SPEED / 100);
	s->pos.y += c * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.y -= c * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '2')
	{
		s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
		s->map.nbspr--;
		parse_sprite(s);
	}
}

void	moving(t_all *s, double c)
{
	s->pos.x += c * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.x -= c * (s->dir.x * SPEED / 100);
	s->pos.y += c * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.y -= c * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '2')
	{
		s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
		s->map.nbspr--;
		parse_sprite(s);
	}
}

void	rotation(t_all *s, double c)
{
	double	distance;

	s->dir.x = s->dir.x * cos(c * TURN) - s->dir.y * sin(c * TURN);
	s->dir.y = s->dir.y * cos(c * TURN) + s->dir.x * sin(c * TURN);
	distance = hypot(s->dir.x, s->dir.y);
	s->dir.x /= distance;
	s->dir.y /= distance;
}
