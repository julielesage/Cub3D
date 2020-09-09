#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> //read
# include <stdlib.h>
# include <string.h>
# include <stdio.h> //printf 
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
int		ft_parse_cub(t_all *s, char *cub);

// libft
int		my_strcmp(char *s1, char *s2);
int		my_get_next_line(int fd, char **line);
char	ft_strchr(char *left, char c);
char	*my_strndup(char *s1, int n);
char	*my_str_join(char *s1, char *s2);
char	*new_line(char *left, char **line, int ret);
int		ft_errorsofree(char *left);
size_t	my_strlen(char *string);
char	*my_substr(char *s1, unsigned int start, size_t len);
char	*my_strchr(char *left, char c);

// utils
int		ft_write_error(int nb);
int		freeAndClose(int ret);

#endif
