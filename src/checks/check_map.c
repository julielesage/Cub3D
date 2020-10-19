#include "../../cub3d.h"

char *fill_map(char *str, int len)
{
  int i;
  char *filled_str;

  i = 0;
  while (str[i])
    i++;
  if (!(filled_str = malloc(sizeof(char) * (i + 1))))
    return NULL;
  i = 0;
  while (str[i] && str[i] != '\0')
    filled_str[i] = str[i];
  while (i < len)
  {
    filled_str[i] = '1';
    i++;
  }
  filled_str[len] = '\0';
  //free(str);
  return filled_str;
}

int check_holes(char *str, int end)
{
  int i;

  i = 0;
  end++;
  while (i < end)
  {
    if (str[i] == ' ')
    {
      if (str[i - 1] != '1')
        return (-1);
      while (str[i] == ' ')
        i++;
      if (str[i] != '1' && str[i] != '\0')
        return (-1);
    }
    i++;
  }
  return (0);
}

int check_columns(t_all *s)
{
  int i;
  int j;
  char *str;
  int length;

  i = 0;
  j = 0;
  while (s->map.tab[j][i]) // ou i < map.x
  {
    while (s->map.tab[j][i])
      j++;
    length = j;
    if (!(str = (char *)malloc(sizeof(char) * (length + 1))))
      return (-1);
    j = 0;
    while (j < length && s->map.tab[j][i])
    {
      str[j] = s->map.tab[j][i];
      j++;
    }
    str[j] = '\0';
    j = check_line(str);
    //free(str);
    if (j < 0)
      return (-1);
    i++;
  }
  return (0);
}

int check_line(char *str)
{
  int i;
  int k;

  i = 0;
  printf("check line : %s\n", str);
  // if str does not begin by 1 = error
  while (str[i] == ' ' && str[i] != '\0')
  {
    printf("i = %d\n", i);
    i++;
  }
  // i++;
  printf("str[i] = %c\n", str[i]);
  if (str[i] != '1' && str[i] != '\0')
    return (-12);
  k = my_strlen(str) - 1;
  // if str does not end by 1 or have leaks = error
  while (k > 0 && str[k] == ' ' && str[k] != '\0')
  {
    printf("k = %d\n", k);
    k--;
  }
  //k--;
  printf("str[k] = %c\n", str[k]);
  if (str[k] != '1' || (check_holes(&str[i], k) == -1))
    return (-12);
  return (0);
}

int check_map_leaks(t_all *s)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (j < s->map.y)
  {
    //printf("s->map.tab[j] line in check_map_leaks(s) : %s\n", s->map.tab[j]);
    if (check_line(s->map.tab[j]) == -12)
      return (write_errors(-12));
    if (s->map.x > my_strlen(s->map.tab[j]))
      if ((s->map.tab[j] = fill_map(s->map.tab[j], s->map.x)) == NULL)
        return (write_errors(-12));
    j++;
  }
  if (check_columns(s) == -1)
    return (write_errors(-12));
  j = 0;
  while (j < s->map.y)
    printf("la tab modifiée par ligne : %s\n", s->map.tab[j]);
  return (0);
}