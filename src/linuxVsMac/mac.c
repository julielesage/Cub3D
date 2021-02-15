/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 22:10:08 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		key_functions(int key, void *arg)
{
	if (key == ESC)
		free_and_close(arg, 1);
	else if (key == W || key == UP)
		moving(arg, 1);
	else if (key == A)
		sidesteping(arg, -1);
	else if (key == S || key == DOWN)
		moving(arg, -1);
	else if (key == D)
		sidesteping(arg, 1);
	else if (key == LEFT)
		rotation(arg, -1);
	else if (key == RIGHT)
		rotation(arg, 1);
	play(arg);
	return (1);
}

int		parse_resolution(t_all *s, char *str, int *i)
{
	if (s->win.x != 0 || s->win.y != 0)
		return (-3);
	(*i)++;
	s->win.x = my_atoi(str, i);
	s->win.y = my_atoi(str, i);
	if (s->win.x > 2560)
		s->win.x = 2560;
	if (s->win.y > 1400)
		s->win.y = 1400;
	skip_spaces(str, i);
	if (s->win.x == 0 || s->win.y == 0 || str[*i] != '\0')
		return (-4);
	return (0);
}
