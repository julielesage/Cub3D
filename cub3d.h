/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/02/10 09:46:04 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx_linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>

# define NONE 0xFF000000
# define RIGHT_CLIC 1
# define LEFT_CLIC 2
# define SCROLL_UP 3
# define SCROLL_DOWN 4

# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# define UP 126
# define DOWN 125

# define LEFT 123
# define RIGHT 124

# define TURN 0.05
# define SPEED 20

typedef struct		s_pos
{
	double			x;
	double			y;
	int				fwd;
	int				bwd;
	int				right;
	int				left;
	int				rotleft;
	int				rotright;
}					t_pos;

typedef struct		s_dir
{
	double			x;
	double			y;
	int				angle;
}					t_dir;

typedef struct		s_map
{
	char			**tab;
	int				x;
	int				y;
	int				nbspr;
}					t_map;

typedef struct		s_err
{
	int				nbr;
	int				map;
	int				pos;
}					t_err;

typedef struct		s_win
{
	int				x;
	int				y;
	void			*ptr;
}					t_win;

typedef struct		s_mlx
{
	void			*ptr;
}					t_mlx;

typedef struct		s_tex
{
	unsigned int	*adr;
	void			*img;
}					t_tex;

typedef struct		s_img
{
	void			*ptr;
	unsigned int	*adr;
	int				fsh;
}					t_img;

typedef struct		s_ray
{
	double			x;
	double			y;
	int				i;
	double			ver;
	double			hor;
}					t_ray;

typedef struct		s_hit
{
	double			x;
	double			y;
	double			distance;
}					t_hit;

typedef struct		s_stk
{
	double			x;
	double			y;
	double			dis;
}					t_stk;

typedef struct		s_spr
{
	double			x;
	double			y;
	double			dis;
}					t_spr;

typedef struct		s_all
{
	t_pos			pos;
	t_dir			dir;
	t_map			map;
	t_err			error;
	t_win			win;
	t_mlx			mlx;
	t_tex			texnorth;
	t_tex			texsouth;
	t_tex			texeast;
	t_tex			texwest;
	t_tex			texspr;
	unsigned int	floor;
	unsigned int	ceil;
	t_img			img;
	t_ray			ray;
	t_hit			hit;
	t_stk			*stock;
	t_spr			*sprite;
}					t_all;

int					main(int argc, char **argv);
void				init_game(char *cub, int save);
void				declare_argv(t_all *s);
int					init_cube(t_all *s, char *cub, int save);
void				declare_rays(t_all *s);
void				declare_textures(t_all *s);

int					verify_argvs(int argc, char **argv);
int					extension_check(char *argv, char *ext);
int					parse_cub(t_all *s, char *cub);
int					distribute_line(t_all *s, char *line);
void				distribute_texture(t_all *s, char *line, int i);
int					parse_map(t_all *s, char *line);
char				*parse_line(t_all *s, char *line);
int					line_length(t_all *s, char *line);
int					parse_resolution(t_all *s, char *str, int *i);
int					parse_texture(t_all *s, t_tex *texture, char *line, int *i);
int					check_map_leaks(t_all *s);
int					check_line(char *str);
int					check_columns(t_all *s);
char				*column_line(char *str, t_all *s, int i, int j);
int					check_holes(char *str, int end);
char				*fill_map(char *str, int len);
int					parse_sprite(t_all *s);
void				get_position(t_all *s);
int					last_checks(t_all *s);

int					make_xpm(t_all *s, t_tex *texture, char *file);
int					get_color(unsigned int *texture, char *line, int *i);
void				color_column(t_all *s, int size);
unsigned int		color_pixel(t_all *s, double i);
void				handle_sprite(t_all *s);
void				unsort_sprite(t_all *s);
void				locate_spr(t_all *s, double spx, double spy, double spdis);
unsigned int		pixelize_spr(t_all *s, int index, unsigned int color);
void				draw_sprite(t_all *s, int loc, double dist);
int					make_bitmap(t_all *s);
void				bm_header(t_all *s, int fd);
void				bm_infos(t_all *s, int fd);
void				bm_data(t_all *s, int fd);

void				build_screen(t_all *s);
void				is_ray(t_all *s);
void				is_direction(t_all *s);
void				is_vertical(t_all *s);
void				is_horizontal(t_all *s);
void				make_stocks(t_all *s);
void				register_ray(t_all *s);
int					size_col(t_all *s);

int					my_strcmp(char *s1, char *s2);
int					my_get_next_line(t_all *s, int fd, char **line);
char				*my_strchr(char *left, char c);
char				*my_strndup(char *s1, int n);
char				*my_str_join(char *s1, char *s2);
char				*new_line(char *left, char **line, int ret);
int					ft_errorsofree(char *left);
int					my_strlen(char *str);
char				*my_substr(char *s1, unsigned int start, size_t len);
int					skip_spaces(char *str, int *i);
int					my_atoi(char *str, int *i);

int					exit_error(t_all *s);
int					write_errors(t_all *s, int err);
void				free_and_close(t_all *s, int win);
void				free_textures(t_all *s);

int					key_functions(int key, t_all *s);
int					key_release(int key, t_all *s);
void				moving(t_all *s, double c);
void				rotation(t_all *s, double c);
void				sidesteping(t_all *s, double c);
void				play(t_all *s);
int					game_loop(t_all *s);

#endif
