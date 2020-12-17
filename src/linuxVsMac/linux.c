#include "../../cub3d.h"

int key_functions(int key, t_all *s)
{
  if (key == 65307)
    free_and_close(s, 1);
  else if (key == 119 || key == 65362)
  { // avance = Z sur azerty
    s->pos.moving = 1;
    moving(s, 1);
  }
  else if (key == 97)
  { // pas chassé vers la gauche
    s->pos.moving = 1;
    sidesteping(s, -1);
  }
  else if (key == 115 || key == 65364)
  { // recule
    s->pos.moving = 1;
    moving(s, -1);
  }
  else if (key == 100)
  { // pas chassé vers la droite
    s->pos.moving = 1;
    sidesteping(s, 1);
  }
  else if (key == 65361)
  { // rotation vers la gauche
    s->pos.moving = 1;
    rotation(s, -1);
  }
  else if (key == 65363)
  { // rotation vers la droite
    s->pos.moving = 1;
    rotation(s, 1);
  }
  play(s);
  return (1);
};

int key_release(int key, t_all *s)
{
  if (key == 119 || key == 65362 || key == 97 || key == 115 || key == 65364 || key == 100 || key == 65361 || key == 65363) // avance = Z sur azerty
    s->pos.moving = 0;
  play(s);
  return (1);
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