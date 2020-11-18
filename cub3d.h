#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx_opengl/mlx.h"
#include <unistd.h> //read
#include <stdlib.h> //malloc
#include <string.h> //gnl
#include <math.h>		// cosinus and co
#include <stdio.h>	//printf
#include <fcntl.h>	//open

#define NONE 0xFF000000
#define RIGHT_CLIC 1
#define LEFT_CLIC 2
#define SCROLL_UP 3
#define SCROLL_DOWN 4

// player position
typedef struct s_pos
{
	double x;
	double y;
} t_pos;

// camera position
typedef struct s_dir
{
	double x;
	double y;
	int angle; // for the view angle
} t_dir;

//map cub
typedef struct s_map
{
	char **tab; // filled in parse_map
	int x;			// = biggest strlen in multiple parse_line
	int y;			// given in parse_map at the end of distributing_line
	int nbspr;
} t_map;

// errors
typedef struct s_err
{
	int nbr; // numéro de la tring error
	int map; // parse-map d'une ligne commencée
	int pos; // si plusieurs positions dans la map
} t_err;

// screen window
typedef struct s_win
{
	int x; // given by parse_resolution
	int y; // given by parse_resolution
	void *ptr;
} t_win;

// libX
typedef struct s_mlx
{
	void *ptr; // xpm data parsed by mlx lib
} t_mlx;

// texture
typedef struct s_tex
{
	unsigned int *n;	 //north
	unsigned int *s;	 //south
	unsigned int *e;	 //east
	unsigned int *w;	 //west
	unsigned int *spr; // sprite
	unsigned int f;		 // floor color
	unsigned int c;		 // ceiling color
} t_tex;

// img mystere
typedef struct s_img
{
	void *ptr;				 // given by mlx_new_image
	unsigned int *adr; //given by mlx_get_color_value pour tab[ray.i]
	int fsh;
} t_img;

typedef struct s_ray // = column = window.x
{
	double x;
	double y;
	int i;
	double ver; // vertical
	double hor; // horizontal
} t_ray;

typedef struct s_hit
{
	double x;
	double y;
	double distance;
} t_hit;

typedef struct s_stk
{
	double x;		// distance to x
	double y;		// distance to y
	double dis; // 1000000000
							//config.set [] ?
} t_stk;			// tab de x

typedef struct s_spr
{
	double x; // given in parse_stripe
	double y;
	double dis;
} t_spr;

// un anneau pour les gouverner tous
typedef struct s_all
{
	t_pos pos;
	t_dir dir;
	t_map map;
	t_err error;
	t_win window;
	t_mlx mlx;
	t_tex texture;
	t_img img;
	t_ray ray;
	t_hit hit;
	t_stk *stock;	 // tab for each x
	t_spr *sprite; // for each sprite avec leur coordonnées pour chacun : [1ery, 1erx, 2ndy, 2ndx, ...]
} t_all;

// src
int main(int argc, char **argv);
void init_game(char *cub, int save);
void declare_argv(t_all *s);
int init_cube(t_all *s, char *cub, int save);
void declare_rays(t_all *s);

// checks
int verify_argvs(int argc, char **argv);
int extensionCheck(char *argv, char *ext);
int parse_cub(t_all *s, char *cub);
int distribute_line(t_all *s, char *line);
int parse_map(t_all *s, char *line);
char *parse_line(t_all *s, char *line);
int line_length(t_all *s, char *line);
int parse_resolution(t_all *s, char *str, int *i);
int parse_texture(t_all *s, unsigned int **addr, char *line, int *i);
int check_map_leaks(t_all *s);
int check_line(char *str, int j);
int check_columns(t_all *s);
int check_holes(char *str, int end);
int parse_sprite(t_all *s);
void get_position(t_all *s);
int last_checks(t_all *s);

// textures
int make_xpm(t_all *s, unsigned int **addr, char *file);
int get_color(unsigned int *addr, char *line, int *i);
void color_column(t_all *s, int size);
unsigned int color_pixel(t_all *s, double i);
void handle_sprite(t_all *s);
void unsort_sprite(t_all *s);
void locate_sprite(t_all *s, double sprx, double spry, double sprdis);
unsigned int pixelize_spr(t_all *s, int index, unsigned int color);
void draw_sprite(t_all *s, int loc, double dist);
int make_bitmap(t_all *s);
void bm_header(t_all *s, int fd);
void bm_infos(t_all *s, int fd);
void bm_data(t_all *s, int fd);

// raycasting
void build_screen(t_all *s);
void isRay(t_all *s);
void isDirection(t_all *s);
void isVertical(t_all *s);
void isHorizontal(t_all *s);
void make_stocks(t_all *s);
void register_ray(t_all *s);
int size_col(t_all *s);

// libft
int my_strcmp(char *s1, char *s2);
int my_get_next_line(int fd, char **line);
char ft_strchr(char *left, char c);
char *my_strndup(char *s1, int n);
char *my_str_join(char *s1, char *s2);
char *new_line(char *left, char **line, int ret);
int ft_errorsofree(char *left);
int my_strlen(char *str);
char *my_substr(char *s1, unsigned int start, size_t len);
char *my_strchr(char *left, char c);
int skip_spaces(char *str, int *i);
int my_atoi(char *str, int *i);

// utils
int exit_error(t_all *s, char *str);
int write_errors(int err);
void free_and_close(t_all *s, int win);
void free_textures(t_all *s);

#endif