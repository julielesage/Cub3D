#include "../../cub3d.h"

void bm_data(t_all *s, int fd)
{
  int i;
  int j;
  unsigned char buffer[4];

  i = s->window.x * (s->window.y - 1);
  while (i >= 0)
  {
    j = 0;
    while (j < s->window.x)
    {
      buffer[0] = (unsigned char)(s->img.adr[i] % 256);
      buffer[1] = (unsigned char)(s->img.adr[i] / 256 % 256);
      buffer[2] = (unsigned char)(s->img.adr[i] / 256 / 256 % 256);
      buffer[3] = (unsigned char)(0);
      write(fd, buffer, 4);
      i++;
      j++;
    }
    i -= 2 * s->window.x;
  }
}

void bm_infos(t_all *s, int fd)
{
  int n;
  unsigned char infos[40];

  n = 0;
  while (n < 40)
    infos[n++] = (unsigned char)(0);
  infos[0] = (unsigned char)(40);
  n = s->window.x;
  infos[4] = (unsigned char)(n % 256);
  infos[5] = (unsigned char)(n / 256 % 256);
  infos[6] = (unsigned char)(n / 256 / 256 % 256);
  infos[7] = (unsigned char)(n / 256 / 256 / 256);
  n = s->window.y;
  infos[8] = (unsigned char)(n % 256);
  infos[9] = (unsigned char)(n / 256 % 256);
  infos[10] = (unsigned char)(n / 256 / 256 % 256);
  infos[11] = (unsigned char)(n / 256 / 256 / 256);
  infos[12] = (unsigned char)(1);
  infos[14] = (unsigned char)(32);
  write(fd, infos, 40);
}

void bm_header(t_all *s, int fd)
{
  int n;
  unsigned char header[14];

  n = 0;
  while (n < 14)
    header[n++] = (unsigned char)(0);
  header[0] = (unsigned char)(66);
  header[1] = (unsigned char)(77);
  n = s->window.x * s->window.y * 4 + 54;
  header[2] = (unsigned char)(n % 256);
  header[3] = (unsigned char)(n / 256 % 256);
  header[4] = (unsigned char)(n / 256 / 256 % 256);
  header[5] = (unsigned char)(n / 256 / 256 / 256);
  header[10] = (unsigned char)(54);
  write(fd, header, 14);
}

int make_bitmap(t_all *s)
{
  // 	t_ray	ray;
  // t_hit	hit;

  // ray.x = 0;
  // ray.y = 0;
  // ray.i = 0;
  // ray.v = 0;
  // ray.w = 0;
  // hit.x = 0;
  // hit.y = 0;
  // hit.d = 0;
  // s->ray = ray;
  // s->hit = hit;
  int fd;

  build_screen(s);
  fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  printf("screen ok");
  bm_header(s, fd);
  bm_infos(s, fd);
  bm_data(s, fd);
  close(fd);
  free(s->img.ptr);
  free(s->img.adr);
  free_and_close(s, 0);
  return (0);
}
