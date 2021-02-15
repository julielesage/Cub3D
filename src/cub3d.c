/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 21:01:08 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		init_cube(t_all *s, char *cub, int save)
{
	t_pos	pos;

	pos.x = 0;
	pos.y = 0;
	pos.right = 0;
	pos.left = 0;
	pos.fwd = 0;
	pos.bwd = 0;
	pos.rotleft = 0;
	pos.rotright = 0;
	s->pos = pos;
	s->mlx.ptr = mlx_init();
	if (parse_cub(s, cub) == -1 || check_map_leaks(s) == -1
		|| parse_sprite(s) == -1 || last_checks(s) == -1)
		free_and_close(s, 0);
	if (save == 1)
		return (make_bitmap(s));
	s->win.ptr = mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, "Cub3D");
	play(s);
	mlx_hook(s->win.ptr, 2, 1L << 0, key_functions, s);
	mlx_hook(s->win.ptr, 3, 1L << 1, key_release, s);
	mlx_hook(s->win.ptr, 17, 1L << 17, exit_error, s);
	mlx_loop_hook(s->mlx.ptr, game_loop, s);
	mlx_loop(s->mlx.ptr);
	return (1);
}

void	declare_textures(t_all *s)
{
	t_tex	texnorth;
	t_tex	texsouth;
	t_tex	texwest;
	t_tex	texeast;
	t_tex	texspr;

	texnorth.img = NULL;
	texnorth.adr = NULL;
	texsouth.img = NULL;
	texsouth.adr = NULL;
	texeast.img = NULL;
	texeast.adr = NULL;
	texwest.img = NULL;
	texwest.adr = NULL;
	texspr.img = NULL;
	texspr.adr = NULL;
	s->texspr = texspr;
	s->texwest = texwest;
	s->texeast = texeast;
	s->texnorth = texnorth;
	s->texsouth = texsouth;
}

void	declare_argv(t_all *s)
{
	t_map	map;
	t_dir	dir;
	t_spr	*sprite;
	t_stk	*stock;

	map.tab = NULL;
	map.x = 0;
	map.y = 0;
	map.nbspr = 0;
	s->map = map;
	s->ceil = 0xFF000000;
	s->floor = 0xFF000000;
	declare_textures(s);
	stock = NULL;
	s->stock = stock;
	dir.x = 0;
	dir.y = 0;
	s->dir = dir;
	sprite = NULL;
	s->sprite = sprite;
}

void	init_game(char *cub, int save)
{
	t_all s;
	t_err error;
	t_win win;
	t_mlx mlx;
	t_img img;

	win.ptr = NULL;
	win.x = 0;
	win.y = 0;
	s.win = win;
	error.nbr = 0;
	error.map = 0;
	error.pos = 0;
	s.error = error;
	mlx.ptr = NULL;
	s.mlx = mlx;
	img.ptr = NULL;
	img.adr = NULL;
	img.fsh = 0;
	s.img = img;
	declare_argv(&s);
	init_cube(&s, cub, save);
}

int		main(int argc, char **argv)
{
	if (verify_argvs(argc, argv) == 1)
		write(2, "Error\nInvalid arguments can not be taken\n", 56);
	return (0);
}
