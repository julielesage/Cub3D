#include "../cub3d.h"

void init_cube(t_all *s, char *cub, int save)
{
	s->mlx.ptr = mlx_init();
	if (parse_cub(s, cub) == -1 || check_map_leaks(s) == -1) // || pos ||slist || parcheck
	{
		free_and_close(s, 0); // ca le mettre à la fin
	}
	// ft_pos(s);
	// s->spr = NULL;
	// ft_slist(s);
	//ft_parcheck
	if (save == 1)
		write(1, "saved\n", 7);
}

void declare_argv(t_all *s)
{
	t_map map;
	t_tex texture;

	map.tab = NULL;
	map.x = 0;
	map.y = 0;
	s->map = map;
	texture.n = NULL;
	texture.s = NULL;
	texture.e = NULL;
	texture.w = NULL;
	texture.spr = NULL;
	texture.c = 0xFF000000;
	texture.f = 0xFF000000;
	s->texture = texture;
}

void init_game(char *cub, int save)
{
	t_all s;
	t_err error;
	t_win window;
	t_mlx mlx; // needed by mlx lib
	t_img img;

	window.ptr = NULL;
	window.x = 0;
	window.y = 0;
	s.window = window;
	error.nbr = 0;
	error.map = 0; //parse map d'une ligne commencée
	error.p = 0;
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

int main(int argc, char **argv)
{
	if (verify_argvs(argc, argv) == 1)
		write(2, "Error\nVerified: invalid arguments can not be taken", 56);
	return 0;
	// if (s.mlx.ptr == 0) init mlx failed
}
