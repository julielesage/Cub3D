#include "../cub3d.h"

int init_cube(t_all *s, char *cub, int save)
{
	t_pos pos;
	pos.x = 0;
	pos.y = 0;
	s->pos = pos;
	s->mlx.ptr = mlx_init();
	if (parse_cub(s, cub) == -1 || check_map_leaks(s) == -1 || parse_sprite(s) == -1 || last_checks(s) == -1)
	{
		free_and_close(s, 0); // stop the game config
	}
	if (save == 1)
		return (make_bitmap(s));
	rotation(s, 1); // 2x pour détruire un sprite si trop près de la première position
	moving(s, 1);
	rotation(s, -1);
	moving(s, -1);
	s->window.ptr = mlx_new_window(s->mlx.ptr, s->window.x, s->window.y, "Cub3D");
	play(s);
	mlx_hook(s->window.ptr, 2, 0, key_functions, s);
	mlx_hook(s->window.ptr, 17, 0, exit_error, s); // 17 = ctrl
	mlx_loop(s->mlx.ptr);

	return (1);
}

void declare_argv(t_all *s)
{
	t_map map;
	t_tex texture;
	t_dir dir;
	t_spr *sprite;
	t_stk *stock;

	map.tab = NULL;
	map.x = 0;
	map.y = 0;
	map.nbspr = 0;
	s->map = map;
	texture.n = NULL;
	texture.s = NULL;
	texture.e = NULL;
	texture.w = NULL;
	texture.spr = NULL;
	texture.c = 0xFF000000;
	texture.f = 0xFF000000;
	s->texture = texture;
	stock = NULL;
	s->stock = stock;
	dir.x = 0;
	dir.y = 0;
	s->dir = dir;
	sprite = NULL;
	s->sprite = sprite;
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
	error.map = 0; //parse map d'une ligne commencée and then ?
	error.pos = 0;
	s.error = error;
	mlx.ptr = NULL;
	s.mlx = mlx;
	img.ptr = NULL; // given by build_screen
	img.adr = NULL; // ?
	img.fsh = 0;		// ?
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
