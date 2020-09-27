#include "../../cub3d.h"

int		my_atoi(char *str, int *i)
{
	int	value;

	value = 0;
	skip_spaces(str, i);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		value = value * 10 + (str[*i] - 48);
		(*i)++;
	}
	return value;
}

int		skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\v'
		|| str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\f')
		(*i)++;
	return 0;
}

char	*my_substr(char *s1, unsigned int start, size_t len)
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
		dst[i] = s1[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return dst;
}
