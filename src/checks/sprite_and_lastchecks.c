#include "../../cub3d.h"

int parse_sprite(t_all *s)
{
  int i;
  int j;
  int k;
  //printf("parsing sprite");
  if (s->sprite)
    s->sprite = NULL; // on refait la liste des sprites si on en a attrapé un
  if (!(s->sprite = malloc(sizeof(t_spr) * s->map.nbspr)))
    return (-1);
  i = 0;
  j = 0;
  while (j < s->map.y) //chaque ligne
  {
    k = 0;
    while (k < s->map.x) // chaque case
    {
      if (s->map.tab[j][k] == '2')
      {
        s->sprite[i].y = (double)j + 0.5;
        s->sprite[i++].x = (double)k + 0.5; // = tab[1ery, 1ery, 2ndy, 2ndx, ...]
      }
      k++;
    }
    j++;
  }
  return (1);
}

int last_checks(t_all *s)
{
  //printf("last checks");
  if (s->window.x <= 0 || s->window.y <= 0)
    return (write_errors(-14));
  else if ((s->texture.n == NULL || s->texture.s == NULL || s->texture.e == NULL) || (s->texture.w == NULL || s->texture.spr == NULL))
    return (write_errors(-15));
  else if (s->texture.c == NONE || s->texture.f == NONE)
    return (write_errors(-16));
  else if (s->error.pos == 0)
    return (write_errors(-17));
  else if (s->error.pos > 1)
    return (write_errors(-18));
  return (1);
}