#include "../../cub3d.h"

void free_textures(t_all *s)
{
	free(s->texture.n);
	free(s->texture.s);
	free(s->texture.e);
	free(s->texture.w);
	free(s->texture.spr);
}

// 	exit(0);
// 	return (1);
// }
// se referer a exit error
void free_and_close(t_all *s, int window)
{ //free tous les s malloc
	int j;

	j = 0;
	while (j < s->map.y)
		free(s->map.tab[j++]);
	free(s->map.tab);
	free_textures(s);
	if (window == 1)
		mlx_destroy_window(s->mlx.ptr, s->window.ptr);
	free(s->mlx.ptr);
	exit(window);
}

// int exit_game(t_all *s, int code)
// {
// 	//clear_config(&s);
// 	// int i;

// 	// i = 0;
// 	// while (i < s->map.y)
// 	// 	free(s->map.tab[i]);
// 	// free(s->map.tab);
// 	clear_window(&s, &s->window);
// 	clear_textures(&s);
// 	clear_sprites(&s->sprite);
// 	exit(code);		 // ou (0) ?
// 	return (code); // besoin ?
// }

int exit_error(t_all *s, char *str)
{
	if (str && s)
		write(2, str, my_strlen(str));
	free_and_close(s, EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int write_errors(int err)
{
	(err == -1) ? write(2, "Error : Couldn't open file (FD)\n", 32) : 0;
	(err == -2) ? write(2, "Error : Couldn't parse cub (GNL)\n", 34) : 0;
	(err == -3) ? write(2, "Error : Resolution specified twice\n", 35) : 0;
	(err == -4) ? write(2, "Error : Invalid resolution\n", 27) : 0;
	(err == -5) ? write(2, "Error : Floor/ceiling specified twice\n", 38) : 0;
	(err == -6) ? write(2, "Error : Invalid floor/ceiling line\n", 35) : 0;
	(err == -7) ? write(2, "Error : Texture path specified twice\n", 37) : 0;
	(err == -8) ? write(2, "Error : Malloc fail (texture path)\n", 35) : 0;
	(err == -9) ? write(2, "Error : Invalid texture image\n", 30) : 0;
	(err == -10) ? write(2, "Error : Invalid line in file\n", 29) : 0;
	(err == -11) ? write(2, "Error : Malloc fail parsing map\n", 32) : 0;
	(err == -12) ? write(2, "Error : Invalid map\n", 20) : 0;
	(err == -13) ? write(2, "Error : Map isn't a rectangle\n", 30) : 0;
	(err == -14) ? write(2, "Error : No resolution specified\n", 32) : 0;
	(err == -15) ? write(2, "Error : Missing texture\n", 24) : 0;
	(err == -16) ? write(2, "Error : Missing floor/ceiling color\n", 26) : 0;
	(err == -17) ? write(2, "Error : No starting position\n", 29) : 0;
	(err == -18) ? write(2, "Error : Multiple starting positions\n", 36) : 0;
	(err == -19) ? write(2, "Error : Map isn't surrounded by walls\n", 38) : 0;
	return (-1);
}
