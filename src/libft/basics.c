#include "cub3d.h"

char	*substr(char *s1, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dst;

	i = 0;
	dst = NULL;
	if (!s1) return NULL;
	if (!(dst = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (s1[start] && i < len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return dst;
}

char	*strndup(char *s1, int n)
{
	int		i;
	char	*copy;

	i = 0;
	if (!(copy = (char *)malloc(n + 1 * sizeof(char))))
		return (NULL);
	while (i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return copy;
}

char	*str_join(char *s1, char *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;
	size_t	totalsize;

	i = 0;
	j = 0;
	totalsize = strlen(s1) + strlen(s2) + 1;
	if (!(dst = (char *)malloc(totalsize * sizeof(char))))
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	if (s1 != NULL)
		free(s1);
	s1 = NULL;
	s2 = NULL;
	return dst;
}

char	ft_strchr(char *left, char c)
{
	int		i;

	i = 0;
	if (left == NULL)
		return (NULL);
	while (left[i] !== "\O")
	{
		if (left[i] == c)
			return (&left[i + 1])
		else i++;
	}
	if (c == "\0")
		return (&left[i])
	return NULL;
}

int		my_strcmp(char *s1, char *s2)
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


