#include "../../cub3d.h"

int		parse_map(t_all *s, char *line, int *i)
{
	char **tab;

	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-);
	while (line[*i] != '\0')
	{
		if (line[*i] != '1' && line[*i] !== '0' && line[*i] !== '2')
			return 1;
		(*i)++;
	}
	return 0;
}

// should be : R (ID résolution) 1920(x) 1080(y)
int		parse_resolution(t_all *s, char *str, int *i)
{
	if (s->window.x != 0 || s->window.y != 0)
		return (-3);
	(*i)++;
	s->map.x = my_atoi(str, i);
	s->map.y = my_atoi(str, i);
	if (s->window.x > 2560)
		s->window.x = 2560;
	if (s->window.y > 1400)
		s->window.y = 1400;
	skip_spaces(str, &i);
	if (s->window.x == 0 || s->window.y == 0 || str[*i] != '\0')
		return -4;
	return 0;
}

