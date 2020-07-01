#include "cub3d.h"

int my_strcmp(char *s1, char *s2)
{
  if (s1 && s2)
  {
    while (*s1 == *s2 && *s1 && *s2)
    {
      s1++;
      s2++;
    }
  }
  else
    return (1);
  return (*s1 - *s2);
}