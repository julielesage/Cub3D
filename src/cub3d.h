#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> //read
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h> //open

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
    char *tab;
} t_map;

// un anneau pour les gouverner tous
typedef struct s_all {
    t_pos pos;
    t_dir dir;
    t_map map;
} t_all;

// src
int		main(int argc, char **argv);
void	ft_init(char *cub, int save);

// checks
int		verify_argvs(int argc, char **argv);
int		extensionCheck(char *argv, char *ext);
int		ft_parse_cub(char *cub);

// libft
int		my_strcmp(char *s1, char *s2);
int		get_next_line(int fd, char **line);
char	ft_strchr(char *left, char c);
// utils
int		ft_write_error(int nb);
