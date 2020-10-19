#include "../../cub3d.h"

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