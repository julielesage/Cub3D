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
  write(1, "alo\n", 4);
  free(s->img.ptr);
  free(s->img.adr);
}

void strafing(t_all *s, double c) // = traverser les murs
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

int key_functions(int key, void *arg)
{
  if (key == ESC)
    free_and_close(arg, 1);
  else if (key == W) // avance
    moving(arg, 1);
  else if (key == A) // strafe = mitrailler  : collision traverser
    strafing(arg, -1);
  else if (key == S) // recule
    moving(arg, -1);
  else if (key == D) //
    strafing(arg, 1);
  else if (key == LEFT) // rotation vers la gauche
    rotation(arg, -1);
  else if (key == RIGHT) // rotation vers la droite
    rotation(arg, 1);
  play(arg);
  return (1);
}

void moving(t_all *s, double c)
{
  //position augmente avec la prise de direction x
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

void rotation(t_all *s, double c) // camera position/direction
//mais pourquoi une fois 1 et une fois -1 après move ?
{
  // RAPPEL
  // 	s->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
  // s->dir.x *= (c == 'W') ? -1 : 1; // dir.x = -1 vers west, 1 vers east
  // s->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
  // s->dir.y *= (c == 'N') ? -1 : 1; // dir.y = -1 vers le nord, 1 vers le sud

  double distance;

  s->dir.x = s->dir.x * cos(c * TURN) - s->dir.y * sin(c * TURN);
  s->dir.y = s->dir.y * cos(c * TURN) + s->dir.x * sin(c * TURN);
  distance = hypot(s->dir.x, s->dir.y);
  s->dir.x /= distance;
  s->dir.y /= distance;
}