#include "../../cub3d.h"

void isHorizontal(t_all *s)
{
  double y;
  double x;

  y = floor(s->pos.y) + s->ray.hor;
  x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
  while ((int)floor(x) > 0 && (int)floor(x) < s->map.x)
  {
    if (s->map.tab[(int)(y - 1 + s->ray.hor)][(int)floor(x)] == '1')
    {
      if (s->hit.distance > hypot(x - s->pos.x, y - s->pos.y))
      {
        s->hit.x = x;
        s->hit.y = y;
        s->hit.distance = hypot(x - s->pos.x, y - s->pos.y); // distance du mur
      }
      return;
    }
    y += (2 * s->ray.hor - 1);
    x += (2 * s->ray.hor - 1) * s->ray.x / s->ray.y;
  }
}

void isVertical(t_all *s)
{
  double x;
  double y;

  x = floor(s->pos.x) + s->ray.ver; // abs math
  y = s->pos.y + (x - s->pos.x) * (s->ray.y / s->ray.x);
  while ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
  {
    if (s->map.tab[(int)floor(y)][(int)(x - 1 + s->ray.ver)] == '1')
    {
      s->hit.x = x;
      s->hit.y = y;
      s->hit.distance = hypot(x - s->pos.x, y - s->pos.y); // distance du mur
      return;
    }
    x += (2 * s->ray.ver - 1);
    y += (2 * s->ray.ver - 1) * s->ray.y / s->ray.x;
  }
  s->hit.x = s->pos.x;
  s->hit.y = s->pos.y;
  s->hit.distance = 1000000000;
}

void isDirection(t_all *s)
{
  if (s->ray.x >= 0) // si y'a encore de la distance en x
    s->ray.ver = 1;  // on avance vers l'est x++
  else
    s->ray.ver = 0;
  if (s->ray.y >= 0) // si y'a encore de la distance en y
    s->ray.hor = 1;  // on avance vers le sud y++
  else
    s->ray.hor = 0;
}

void isRay(t_all *s)
{
  double angle;
  double distance;

  angle = ((double)s->ray.i - (s->window.x / 2)) * 33 / (s->window.x / 2); // radians
  // ((0 - (1920/2)) *33) /(1920/2)
  // -960 *33 /960 = 33
  // si i = 45 angle = -31, 45

  angle = angle * M_PI / 180; // = -0,5 // = degrés
  s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
  s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
  distance = hypot(s->ray.x, s->ray.y);
  s->ray.x /= distance;
  s->ray.y /= distance;
}

void build_screen(t_all *s)
{
  int bpp; // bits per pixel
  int size_line;
  int endian;
  printf("building screen\n");
  s->img.ptr = mlx_new_image(s->mlx.ptr, s->window.x, s->window.y);
  // return a list of mlx.ptr->img.list + width + height + vertexes map + a buffer of (4*w*h) nb of 0
  s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &size_line, &endian);
  // filling info from img.ptr and returning buffer
  s->stock = malloc(sizeof(t_stk) * s->window.x); // stock de chaque distance par case de map
  while (s->ray.i < s->window.x)
  {
    isRay(s);
    isDirection(s);
    isVertical(s);
    isHorizontal(s);
    register_ray(s);
    color_column(s, size_col(s));
    s->ray.i++;
  }
  handle_sprite(s);
}