#include "../../cub3d.h"

int key_functions(int key, void *arg)
{
  if (key == ESC)
    free_and_close(arg, 1);
  else if (key == W || key == UP) // avance = Z sur azerty
    moving(arg, 1);
  else if (key == A) // pas chassé vers la gauche
    sidesteping(arg, -1);
  else if (key == S || key == DOWN) // recule
    moving(arg, -1);
  else if (key == D) // pas chassé vers la droite
    sidesteping(arg, 1);
  else if (key == LEFT) // rotation vers la gauche
    rotation(arg, -1);
  else if (key == RIGHT) // rotation vers la droite
    rotation(arg, 1);
  play(arg);
  return (1);
};

// should be : R (ID résolution) 1920(x) 1080(y)
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