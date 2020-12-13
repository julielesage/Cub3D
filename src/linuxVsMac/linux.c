#include "../../cub3d.h"

int key_functions(int key, void *arg)
{
  if (key == 65307)
    free_and_close(arg, 1);
  else if (key == 119 || key == 65362) // avance = Z sur azerty
    moving(arg, 1);
  else if (key == 97) // pas chassé vers la gauche
    sidesteping(arg, -1);
  else if (key == 115 || key == 65364) // recule
    moving(arg, -1);
  else if (key == 100) // pas chassé vers la droite
    sidesteping(arg, 1);
  else if (key == 65361) // rotation vers la gauche
    rotation(arg, -1);
  else if (key == 65363) // rotation vers la droite
    rotation(arg, 1);
  play(arg);
  return (1);
};

int parse_resolution(t_all *s, char *str, int *i)
{
  if (s->window.x != 0 || s->window.y != 0)
    return (-3);
  (*i)++;
  s->window.x = my_atoi(str, i);
  s->window.y = my_atoi(str, i);
  if (s->window.x > 2560)
    s->window.x = 2560;
  if (s->window.y > 1400)
    s->window.y = 1400;
  skip_spaces(str, i);
  if (s->window.x == 0 || s->window.y == 0 || str[*i] != '\0')
    return -4;
  return 0;
};

int parse_resolution(t_all *s, char *str, int *i)
{
  int screenx_max;
  int screeny_max;

  if (s->window.x != 0 || s->window.y != 0)
    return (-3);
  (*i)++;
  s->window.x = my_atoi(str, i);
  s->window.y = my_atoi(str, i);
  mlx_get_screen_size(s->mlx.ptr, &screenx_max, &screeny_max);
  if (s->window.x > screenx_max)
    s->window.x = screenx_max;
  if (s->window.y > screeny_max)
    s->window.y = screeny_max;
  skip_spaces(str, i);
  if (s->window.x == 0 || s->window.y == 0 || str[*i] != '\0')
    return -4;
  return 0;
};