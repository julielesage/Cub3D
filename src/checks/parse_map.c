#include "../../cub3d.h"

char *parse_line(t_all *s, char *line, int *i)
{
	char *str;
	int j;

	j = 0;
	if (!(str = (char *)malloc(sizeof(char) * (my_strlen(line) + 1))))
		return (NULL);
	while (line[*i] != '\0')
	{

		if (line[*i] != '0' && line[*i] != '1' && line[*i] != ' ' && line[*i] != '2' && line[*i] != 'E' && line[*i] != 'W' && line[*i] != 'S' && line[*i] != 'N')
		{
			free(str);
			return (NULL);
		}
		else if (line[*i] == '2')
			s->map.sprite++; // FR ca sert a quoi ?
		str[j++] = line[*i];
		(*i)++;
	}
	str[j] = '\0';
	if (my_strlen(str) > s->map.x)
		s->map.x = my_strlen(str);
	return (str); //return a clean line and bigger length in map.x
}

int parse_map(t_all *s, char *line, int *i) // remplit la map tab ligne par ligne
{
	char **tmp;
	int j;

	j = -1; // j = **tab line
	s->error.map = 1;
	// allocation for x strings, x = y resolution
	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-11);
	while (++j < s->map.y)																// 0 at first, then +1 each tour
		tmp[j] = s->map.tab[j];															// copying map.tab if already half full
	if ((tmp[s->map.y] = parse_line(s, line, i)) == NULL) // if last tmp line = got wrong data, otherwise = line
	{
		free(tmp);
		return (-12);
	}
	printf("tmp[j] dans parse map apres parse line = %s\n", tmp[s->map.y]);
	tmp[s->map.y + 1] = NULL; //preparing next y
	if (s->map.y > 0)
		free(s->map.tab); // = free the old tmp
	s->map.tab = tmp;		// replacing old tab with new + one line
	s->map.y++;
	return (0);
}

// should be NO/SO/WE/EA ./path_to_texture
int parse_texture(t_all *s, unsigned int **addr, char *line, int *i)
{
	int j;
	char *file;
	// if already exists
	if (*addr != NULL)
		return (-7);
	(*i) += 2;
	skip_spaces(line, i);
	j = *i;
	while (line[*i] != '\0' && line[*i] != ' ')
		(*i)++;
	if (!(file = (char *)malloc(sizeof(char *) * (*i + 1))))
		return (-8);
	*i = j; // = ' '
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++]; //
	file[j] = '\0';
	j = make_xpm(s, addr, file); // 0 ou moins si error
	free(file);
	return (j);
}

// should be : R (ID résolution) 1920(x) 1080(y)
int parse_resolution(t_all *s, char *str, int *i)
{
	if (s->window.x != 0 || s->window.y != 0)
		return (-3);
	(*i)++;
	s->window.x = my_atoi(str, i);
	s->window.y = my_atoi(str, i);
	if (s->window.x > 2560)
		s->window.x = 2560;
	if (s->window.y > 1400)
		s->window.y = 1400;
	skip_spaces(str, i);
	if (s->window.x == 0 || s->window.y == 0 || str[*i] != '\0')
		return -4;
	return 0;
}