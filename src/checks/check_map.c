#include "../../cub3d.h"

char *fill_map(char *str, int len)
{
  int i;
  char *filled_str;

  i = 0;
  printf("filling map ?");
  if (!(filled_str = malloc(sizeof(char) * (len))))
    return NULL;
  i = 0;
  while (str[i] && str[i] != '\0')
  {
    filled_str[i] = str[i];
    i++;
  }
  while (i < len)
  {
    filled_str[i] = '1';
    i++;
  }
  filled_str[len] = '\0'; // n° 7
  free(str);
  printf("return : %s\n", filled_str);
  return filled_str;
}

int check_holes(char *str, int end)
{
  int i;

  i = 0;
  printf("holes in %s ? \n", str);
  printf("end : %d\n", end);
  while (i < end)
  {
    if (str[i] == ' ')
    {
      printf("i = %d, str[i] = %c, str[i-1] = %c\n", i, str[i], str[i - 1]);
      if (i != 0 && str[i - 1] != '1')
        return (-1);
      while (str[i] == ' ')
        i++;

      if (str[i] != '1' && str[i - 1] != '1' && str[i - 1] != ' ')
        return (-1);

      if (str[i] != '1' && str[i] != '\0')
        return (-1);
    }
    i++;
  }
  printf("check holes ok\n");
  return (0);
}

int check_columns(t_all *s)
{
  int i;
  int j;
  char *str;

  i = 0;
  j = 0;
  while (i < s->map.x - 1) // sans le '/0'
  {
    if (!(str = (char *)malloc(sizeof(char) * (s->map.y + 1))))
      return (-1);
    while (j < s->map.y && (s->map.tab[j][i] == '1' || s->map.tab[j][i] == '0' || s->map.tab[j][i] == ' ' || s->map.tab[j][i] == 'N' || s->map.tab[j][i] == 'S' || s->map.tab[j][i] == 'W' || s->map.tab[j][i] == 'E' || s->map.tab[j][i] == '2'))
    {
      str[j] = s->map.tab[j][i];
      j++;
    }
    str[j] = '\0';
    printf("column = %s\n", str);
    j = check_line(str, i);
    free(str);
    if (j < 0)
      return (-1);
    i++;
  }
  printf("check-columns ok\n");
  return (0);
}

int check_line(char *str, int j)
{
  int i;
  int k;

  i = 0;
  printf("check line %d : %s\n", j, str);
  // if str does not begin by 1 = error
  while (str[i] == ' ' && str[i] != '\0')
    i++;
  if (str[i] != '1' && str[i] != '\0')
    return (-12);
  k = my_strlen(str) - 1;
  // if str does not end by 1 or have leaks = error
  printf("k (my_strlen(str) - 1) = %d et ascii  = %d\n", k, (int)str[k]);
  while (k > 0 && (str[k] == 32 || (int)str[k] < 0) && str[k] != '\0')
  {
    printf("ascci de k = %d\n then minus k", (int)str[k]);
    k--;
  }
  printf("str[first] at i=%d : %c et str[last] at k=%d : %c\n", i, str[i], k, str[k]);
  if (str[k] != '1' || (check_holes(&str[i], k + 1 - i) == -1))
    return (-12);
  printf("check line ok, next\n");
  return (0);
}

int check_map_leaks(t_all *s)
{
  int i;
  int j;

  i = 0;
  j = 0;
  //s->map.y++;
  //printf("map.y ==> %d", s->map.y);
  while (j < s->map.y)
  {
    //printf("s->map.tab[j] line in check_map_leaks(s) : %s\n", s->map.tab[j]);
    if (check_line(s->map.tab[j], j) == -12)
      return (write_errors(-12));
    printf("x = %d , strlen = %d\n", s->map.x, my_strlen(s->map.tab[j]));
    j++;
  }
  if (check_columns(s) == -1)
    return (write_errors(-12));
  j = 0;
  while (j < s->map.y)
  {
    if (s->map.x > my_strlen(s->map.tab[j]) + 1) // si il reste du vide après le '/0'
      if ((s->map.tab[j] = fill_map(s->map.tab[j], s->map.x)) == NULL)
        return (write_errors(-12));
    j++;
  }
  return (0);
}