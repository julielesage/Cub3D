#include "../../cub3d.h"

void play(t_all *s)
{
  t_ray ray;
  t_hit hit;

  ray.x = 0;
  ray.y = 0;
  ray.i = 0;
  ray.ver = 0;
  ray.hor = 0;
  hit.x = 0;
  hit.y = 0;
  hit.distance = 0;
  s->ray = ray;
  s->hit = hit;
  build_screen(s);
  mlx_put_image_to_window(s->mlx.ptr, s->window.ptr, s->img.ptr, 0, 0);
  free(s->img.ptr);
  free(s->img.adr);
}

void sidesteping(t_all *s, double c) // = traverser les murs
{
  if (s->pos.moving == 1)
  {
    s->pos.x -= c * (s->dir.y * SPEED / 100);
    if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
      s->pos.x += c * (s->dir.y * SPEED / 100);
    s->pos.y += c * (s->dir.x * SPEED / 100);
    if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
      s->pos.y -= c * (s->dir.x * SPEED / 100);
    if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '2')
    {
      s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
      s->map.nbspr--;
      parse_sprite(s);
    }
  }
}

void moving(t_all *s, double c)
{
  if (s->pos.moving == 1)
  { //position augmente avec la prise de direction x
    s->pos.x += c * (s->dir.x * SPEED / 100);
    //si on a avancé dans un mur on recule = rester au meme point
    if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
      s->pos.x -= c * (s->dir.x * SPEED / 100);
    //position y augmente avec la prise de direction y
    s->pos.y += c * (s->dir.y * SPEED / 100);
    //si on a avancé dans un mur on recule = rester au meme point
    if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
      s->pos.y -= c * (s->dir.y * SPEED / 100);
    //si on a avancé au final sur un sprite
    if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '2')
    {
      //le sprite devient 0
      s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
      s->map.nbspr--;  // diminue le nb de sprite
      parse_sprite(s); // on refait la liste de sprite avec chacun leur position
    }
  }
}

void rotation(t_all *s, double c) // camera position/direction
{
  // RAPPEL
  // 	s->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
  // s->dir.x *= (c == 'W') ? -1 : 1; // dir.x = -1 vers west, 1 vers east
  // s->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
  // s->dir.y *= (c == 'N') ? -1 : 1; // dir.y = -1 vers le nord, 1 vers le sud
  if (s->pos.moving == 1)
  {
    double distance;

    s->dir.x = s->dir.x * cos(c * TURN) - s->dir.y * sin(c * TURN);
    s->dir.y = s->dir.y * cos(c * TURN) + s->dir.x * sin(c * TURN);
    distance = hypot(s->dir.x, s->dir.y);
    s->dir.x /= distance;
    s->dir.y /= distance;
  }
}