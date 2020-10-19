#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx_opengl/mlx.h"
#include <unistd.h> //read
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h> //printf
#include <fcntl.h> //open

#define NONE 0xFF000000

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
	int a; // for the view angle
} t_dir;

//map cub
typedef struct s_map
{
	char **tab; // filled in parse_map
	int x;			// = biggest strlen in multiple parse_line
	int y;			// given in parse_map at the end of distributing_line
	int sprite;
} t_map;

// errors
typedef struct s_err
{
	int nbr; // numéro de la tring error
	int map; // parse-map d'une ligne commencée
	int p;
} t_err;

// screen window
typedef struct s_win
{
	int x;
	int y;
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
	void *ptr;
	unsigned int *adr;
	int fsh;
} t_img;

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
} t_all;

// src
int main(int argc, char **argv);
void init_game(char *cub, int save);
void declare_argv(t_all *s);
void init_cube(t_all *s, char *cub, int save);

// checks
int verify_argvs(int argc, char **argv);
int extensionCheck(char *argv, char *ext);
int parse_cub(t_all *s, char *cub);
int distribute_line(t_all *s, char *line);
int parse_map(t_all *s, char *line, int *i);
char *parse_line(t_all *s, char *line, int *i);
int line_length(t_all *s, char *line);
int parse_resolution(t_all *s, char *str, int *i);
int parse_texture(t_all *s, unsigned int **addr, char *line, int *i);
int check_map_leaks(t_all *s);
int check_line(char *str);
int check_columns(t_all *s);
int check_holes(char *str, int end);

// textures
int make_xpm(t_all *s, unsigned int **addr, char *file);
int get_color(unsigned int *addr, char *line, int *i);

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
int exit_errors(t_all *s, char *str);
int write_errors(int err);
int free_and_close(t_all *s, int ret);

#endif
