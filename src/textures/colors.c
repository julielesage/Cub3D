#include "../../cub3d.h"

unsigned int color_pixel(t_all *s, double i)
{
  int index;

  if (floor(s->hit.y) == s->hit.y) // si on arrive à une ligne pile
  {
    index = 64 * floor(64 * i) + 64 * (s->hit.x - floor(s->hit.x)); // 64 bpp * point/size_col + 64 * hit.x
    if (s->ray.hor == 1)                                            // = on avance vers le sud
      return (s->texture.s[index]);
    else if (s->ray.hor == 0)
      return (s->texture.n[index]);
  }
  else if (floor(s->hit.x) == s->hit.x) // si on arrive à une ligne pile
  {
    index = 64 * floor(64 * i) + 64 * (s->hit.y - floor(s->hit.y));
    if (s->ray.ver == 1) // on avance vers l'est
      return (s->texture.e[index]);
    else if (s->ray.ver == 0)
      return (s->texture.w[index]);
  }
  return (0x00000000); // = noir
}

void color_column(t_all *s, int size)
{
  unsigned int color;
  int start;
  int count;

  start = s->window.x * (s->window.y - size) / 2;
  if (size > s->window.y)
    count = (size - s->window.y) / 2;
  else
    count = 0;
  color = s->texture.c;                        // ceiling
  while (s->ray.i < s->window.x * s->window.y) // tant que i n'est pas à la fin de la résolution
  {
    if (s->ray.i >= start && count < size)
    {
      color = color_pixel(s, (double)count / size); // on remplit la case ray.i avec la data couleur de texture nsew
      count++;
    }
    else if (count == size)
      color = s->texture.f;                                        // pour floor
    s->img.adr[s->ray.i] = mlx_get_color_value(s->mlx.ptr, color); // met la couleur du floor dans l'adresse img.adr[ray.i]
    s->ray.i += s->window.x;                                       // passer au i suivant = + le nombre de x pour arriver à y++ de la colonne
  }
  s->ray.i -= s->window.x * s->window.y; // retour à i originel pour build_screen
}

int get_color(unsigned int *addr, char *line, int *i)
{
  int r;
  int g;
  int b;

  if (*addr != NONE)
    return (-5);
  // *i = F or C
  (*i)++;               // = ' '
  r = my_atoi(line, i); // i = ','
  (*i)++;
  g = my_atoi(line, i); // i = ','
  (*i)++;
  b = my_atoi(line, i);
  skip_spaces(line, i);
  if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
    return (-6);
  // getting pantone : 256*256 = 65536
  *addr = r * 65536 + g * 256 + b;
  return (0);
};