#include "../../cub3d.h"

void get_position(t_all *s)
{
	char c;
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < s->map.y) // pour chaque ligne
	{
		while (++j < s->map.x) // pour chaque colonne
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->pos.y = (double)i + 0.5; // 0;5 pour milieu de case
				s->pos.x = (double)j + 0.5;
				s->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
				s->dir.x *= (c == 'W') ? -1 : 1; // dir.x = -1 vers west, 1 vers east
				s->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
				s->dir.y *= (c == 'N') ? -1 : 1; // dir.y = -1 vers le nord, 1 vers le sud
				s->error.pos++;									 // si plusieurs positions
			}
		}
		j = -1;
	}
}

char *parse_line(t_all *s, char *line)
{
	char *str;
	int j;
	int i;

	j = 0;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (my_strlen(line) + 1))))
		return (NULL);
	while (line[i] != '\0')
	{

		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '2' && line[i] != 'E' && line[i] != 'W' && line[i] != 'S' && line[i] != 'N')
		{
			free(str);
			return (NULL);
		}
		else if (line[i] == '2')
			s->map.nbspr++; // nb de sprite
		str[j++] = line[i];
		i++;
	}
	str[j] = '\0';
	if (my_strlen(str) > s->map.x)
		s->map.x = my_strlen(str) + 1; // pour le '/0'
	return (str);										 //return a clean line and bigger length in map.x
}

int parse_map(t_all *s, char *line) // remplit la map tab ligne par ligne
{
	char **tmp;
	int j;

	j = -1; // j = **tab line
	s->error.map = 1;
	// allocation for x strings, x = y resolution
	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-11);
	while (++j < s->map.y)														 // 0 at first, then +1 each tour
		tmp[j] = s->map.tab[j];													 // copying map.tab if already half full
	if ((tmp[s->map.y] = parse_line(s, line)) == NULL) // if last tmp line = got wrong data, otherwise = line
	{
		free(tmp);
		return (-12);
	}
	//printf("tmp[j] dans parse map apres parse line j = %d : %s\n", j, tmp[s->map.y]);
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
	//printf("texture file : %s\n", file);
	j = make_xpm(s, addr, file); // 0 ou moins si error
	free(file);
	return (j);
}
