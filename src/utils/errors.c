/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/02/05 10:42:13 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_textures(t_all *s)
{
	if (s->texnorth.img != NULL || s->texnorth.adr != NULL)
		mlx_destroy_image(s->mlx.ptr, s->texnorth.img);
	if (s->texsouth.img != NULL || s->texsouth.adr != NULL)
		mlx_destroy_image(s->mlx.ptr, s->texsouth.img);
	if (s->texeast.img != NULL || s->texeast.adr != NULL)
		mlx_destroy_image(s->mlx.ptr, s->texeast.img);
	if (s->texwest.img != NULL || s->texwest.adr != NULL)
		mlx_destroy_image(s->mlx.ptr, s->texwest.img);
	if (s->texspr.img != NULL || s->texspr.adr != NULL)
		mlx_destroy_image(s->mlx.ptr, s->texspr.img);
	if (s->img.ptr != NULL)
		mlx_destroy_image(s->mlx.ptr, s->img.ptr);
}

void	free_and_close(t_all *s, int window)
{
	int	j;

	j = 0;
	while (j < s->map.y)
		free(s->map.tab[j++]);
	free(s->map.tab);
	free_textures(s);
	if (window == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	exit(window);
}

int		exit_error(t_all *s)
{
	free_and_close(s, 1);
	return (1);
}

int		write_errors(t_all *s, int err)
{
	write(2, "Error\n", 7);
	(err == -20) ? write(2, "Couldn't open file (FD)\n", 24) : 0;
	(err == -2) ? write(2, "Couldn't parse cub (GNL)\n", 25) : 0;
	(err == -3) ? write(2, "Resolution specified twice\n", 28) : 0;
	(err == -4) ? write(2, "Invalid resolution\n", 19) : 0;
	(err == -5) ? write(2, "Floor/ceiling specified twice\n", 30) : 0;
	(err == -6) ? write(2, "Invalid floor/ceiling line\n", 27) : 0;
	(err == -7) ? write(2, "Texture path specified twice\n", 29) : 0;
	(err == -8) ? write(2, "Malloc fail (texture path)\n", 27) : 0;
	(err == -9) ? write(2, "Invalid texture\n", 16) : 0;
	(err == -10) ? write(2, "Invalid line in .cub file\n", 26) : 0;
	(err == -11) ? write(2, "Malloc fail parsing map\n", 24) : 0;
	(err == -12) ? write(2, "Invalid map\n", 12) : 0;
	(err == -13) ? write(2, "Map isn't a rectangle\n", 22) : 0;
	(err == -14) ? write(2, "No resolution specified\n", 24) : 0;
	(err == -15) ? write(2, "Missing texture\n", 16) : 0;
	(err == -16) ? write(2, "Missing floor/ceiling color\n", 28) : 0;
	(err == -17) ? write(2, "No starting position\n", 21) : 0;
	(err == -18) ? write(2, "Multiple starting positions\n", 28) : 0;
	(err == -19) ? write(2, "Map isn't surrounded by walls\n", 30) : 0;
	s->error.map = -1;
	free_and_close(s, 0);
	return (-1);
}
