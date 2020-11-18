#include "../../cub3d.h"

int size_col(t_all *s)
{
  double correc;
  double fisheye;

  fisheye = fabs((double)s->ray.i / (s->window.x / 2) - 1); // valeur absolue d'un float (x.i / 960)
  fisheye *= 28 * M_PI / 180;
  correc = (double)s->hit.distance * cos(fisheye);
  return (round(s->window.y / correc));
}

void register_ray(t_all *s)
{
  s->stock[s->ray.i].x = s->ray.x;
  s->stock[s->ray.i].y = s->ray.y;
  s->stock[s->ray.i].dis = s->hit.distance;
}