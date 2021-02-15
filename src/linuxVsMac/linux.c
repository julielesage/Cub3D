/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 22:09:00 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		key_functions(int key, t_all *s)
{
	if (key == 65307)
		free_and_close(s, 1);
	else if (key == 119 || key == 65362)
		s->pos.fwd = 1;
	else if (key == 97)
		s->pos.left = 1;
	else if (key == 115 || key == 65364)
		s->pos.bwd = 1;
	else if (key == 100)
		s->pos.right = 1;
	else if (key == 65361)
		s->pos.rotleft = 1;
	else if (key == 65363)
		s->pos.rotright = 1;
	return (1);
}

int		key_release(int key, t_all *s)
{
	if (key == 119 || key == 65362)
		s->pos.fwd = 0;
	else if (key == 97)
		s->pos.left = 0;
	else if (key == 115 || key == 65364)
		s->pos.bwd = 0;
	else if (key == 100)
		s->pos.right = 0;
	else if (key == 65361)
		s->pos.rotleft = 0;
	else if (key == 65363)
		s->pos.rotright = 0;
	return (1);
}

int		parse_resolution(t_all *s, char *str, int *i)
{
	int	screenx_max;
	int	screeny_max;

	if (s->win.x != 0 || s->win.y != 0)
		return (-3);
	(*i)++;
	s->win.x = my_atoi(str, i);
	s->win.y = my_atoi(str, i);
	mlx_get_screen_size(s->mlx.ptr, &screenx_max, &screeny_max);
	if (s->win.x > screenx_max)
		s->win.x = screenx_max;
	if (s->win.y > screeny_max)
		s->win.y = screeny_max;
	skip_spaces(str, i);
	if (s->win.x == 0 || s->win.y == 0 || str[*i] != '\0')
		return (-4);
	return (0);
}
