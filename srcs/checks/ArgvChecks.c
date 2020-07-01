int extensionCheck(char *argv, char *ext)
{
  int i;

  i = 0;
  while (arg[i] != '\0')
    i++;
  if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1]) && (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
    return (1);
  return (0);
}