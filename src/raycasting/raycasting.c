/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 22:12:50 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		size_col(t_all *s)
{
	double	correc;
	double	fisheye;

	fisheye = fabs((double)s->ray.i / (s->win.x / 2) - 1);
	fisheye *= 28 * M_PI / 180;
	correc = (double)s->hit.distance * cos(fisheye);
	return (round(s->win.y / correc));
}

void	register_ray(t_all *s)
{
	s->stock[s->ray.i].x = s->ray.x;
	s->stock[s->ray.i].y = s->ray.y;
	s->stock[s->ray.i].dis = s->hit.distance;
}
