#include "../cub3d.h"

void	init_cube(t_all *s, char *cub, int save)
{
	//s->....ptr = mlx_init();
	if(ft_parse_cub(s, cub) == 1)
	{
		printf("mauvais parsing");
		freeAndClose(0);
	}
	if(save == 1)
		write(1, "saved\n", 7);
}

void	declare_argv(t_all *s)
{
	t_map	map;
	t_tex	texture;

	map.tab = NULL;
	map.x = 0;
	map.y = 0;
	s->map = map;
	texture.n = NULL;
	texture.s = NULL;
	texture.e = NULL;
	texture.w = NULL;
	s->texture = texture;
}

void	init_game(char *cub, int save)
{
	t_all	s;
	t_err	error;
	t_win	window;

//	win.ptr = NULL;
	window.x = 0;
	window.y = 0;
	error.nbr = 0;
//	err.m = 0;
//	err.p = 0;
	s.window = window;
	s.error = error;
	declare_argv(&s);
	init_cube(&s, cub, save);
}

int		main(int argc, char **argv)
{
	if (verify_argvs(argc, argv) == 1)
		write(2,"Error\nVerified: invalid arguments can not be taken", 56);
	return 0;

}
