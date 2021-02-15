/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 21:20:37 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_position(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < s->map.y)
	{
		while (++j < s->map.x)
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->pos.y = (double)i + 0.5;
				s->pos.x = (double)j + 0.5;
				s->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
				s->dir.x *= (c == 'W') ? -1 : 1;
				s->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
				s->dir.y *= (c == 'N') ? -1 : 1;
				s->error.pos++;
			}
		}
		j = -1;
	}
}

char	*parse_line(t_all *s, char *line)
{
	char	*str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (my_strlen(line) + 1))))
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '2'
		&& line[i] != 'E' && line[i] != 'W' && line[i] != 'S' && line[i] != 'N')
		{
			free(str);
			return (NULL);
		}
		else if (line[i] == '2')
			s->map.nbspr++;
		str[j++] = line[i];
		i++;
	}
	str[j] = '\0';
	if (my_strlen(str) > s->map.x)
		s->map.x = my_strlen(str) + 1;
	return (str);
}

int		parse_map(t_all *s, char *line)
{
	char	**tmp;
	int		j;

	j = -1;
	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-11);
	while (++j < s->map.y)
		tmp[j] = s->map.tab[j];
	if ((tmp[s->map.y] = parse_line(s, line)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[s->map.y + 1] = NULL;
	if (s->map.y > 0)
		free(s->map.tab);
	s->map.tab = tmp;
	s->map.y++;
	return (0);
}

int		parse_texture(t_all *s, t_tex *texture, char *line, int *i)
{
	int		j;
	char	*file;

	if (texture->adr != NULL)
		return (-7);
	(*i) += 2;
	skip_spaces(line, i);
	j = *i;
	while (line[*i] != '\0' && line[*i] != ' ')
		(*i)++;
	if (!(file = (char *)malloc(sizeof(char *) * (*i + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = make_xpm(s, texture, file);
	free(file);
	return (j);
}
