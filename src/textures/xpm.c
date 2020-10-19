#include "../../cub3d.h"

int make_xpm(t_all *s, unsigned int **addr, char *file)
{
  void *img;
  int tab[5]; // width, height, bits/pixel, size line, endian

  if (extensionCheck(file, "xpm") == 1)
    return (-1);
  img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
  // well too complicate to tell what's inside...
  // check file size and fd, delete comments,
  // mlx_int_parse_xpm
  // an img_list with each img its width, height, vertexes, buffer from xpm files
  if (img == 0 || tab[0] != 64 || tab[1] != 64)
    return (-1);
  *addr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
  //data from img to addr = img.buffer, bits = UNIQ_BPP*8, size = img.width*UNIQ_BPP, endian = 0
  free(img);
  return (0);
}