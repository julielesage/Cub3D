#include "../../cub3d.h"

int		parse_map(t_all *s, char *line, int *i)
{
	char **tab;

	if (!(tab = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-11);
	while (line[*i] != '\0')
	{
		if (line[*i] != '1' && line[*i] != '0' && line[*i] != '2')
			return 1;
		(*i)++;
	}
	return 0;
}

// should be NO/SO/WE/EA ./path_to_texture
int		parse_texture(t_all *s, unsigned int **addr, char *line, int *i)
{
	int		j;
	char	*file;
	//already exists
	if(*addr != NULL)
		return (-7);
	(*i) += 2;
	skip_spaces(line, i);
	j = *i;
	while (line[*i] != '\0' && line[*i] != ' ')
		(*i)++;
	if(!(file = (char *)malloc(sizeof(char *) * (*i + 1))))
		return (-8);
	*i = j;// = ' '
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++]; // 
	file[j] = '\0';
	write(1, "a\n", 2);
	printf("%s\n", file);
	s->error.nbr = 56;
//	j = make_xpm(s, adr, file);
	return(1);
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
	skip_spaces(str, i);
	if (s->window.x == 0 || s->window.y == 0 || str[*i] != '\0')
		return -4;
	return 0;
}

