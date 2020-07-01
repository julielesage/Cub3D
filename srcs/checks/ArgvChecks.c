#include "cub3d.h"

int extensionCheck(char *argv, char *ext)
{
  int i;

  i = 0;
  while (argv[i] != '\0')
    i++;
  if ((i > 4 && argv[i - 1] == ext[2] && argv[i - 2] == ext[1]) && (argv[i - 3] == ext[0] && argv[i - 4] == '.'))
    return (0);
  return (1);
}