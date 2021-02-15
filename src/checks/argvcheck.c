/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvcheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 23:20:42 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	distribute_texture(t_all *s, char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texnorth, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texsouth, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texwest, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texeast, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		s->error.nbr = parse_texture(s, &s->texspr, line, &i);
}

int		distribute_line(t_all *s, char *line)
{
	int i;

	i = 0;
	skip_spaces(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		s->error.nbr = parse_resolution(s, line, &i);
	else if (my_strchr("NSWES", line[i]) != NULL)
		distribute_texture(s, line, i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->error.nbr = get_color(&s->floor, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->error.nbr = get_color(&s->ceil, line, &i);
	else if (line[i] == '1' && line[i + 1] != '\0')
		s->error.nbr = parse_map(s, line);
	else if (my_strchr("RNSWESFC1", line[i]) == NULL)
	{
		s->error.nbr = -10;
		s->error.map = -1;
	}
	return (s->error.nbr < 0 ? write_errors(s, s->error.nbr) : 0);
}

int		parse_cub(t_all *s, char *cub)
{
	int		ret;
	int		fd;
	char	*line;

	line = NULL;
	if ((fd = open(cub, O_RDONLY)) < 0)
		return (write_errors(s, -20));
	while ((ret = my_get_next_line(s, fd, &line)) > 0)
	{
		if (distribute_line(s, line) == -1)
			ret = -1;
		free(line);
		line = NULL;
	}
	if (distribute_line(s, line) == -1)
		ret = -1;
	free(line);
	close(fd);
	if (ret < 0)
		return (write_errors(s, -2));
	get_position(s);
	return (0);
}

int		extension_check(char *argv, char *ext)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
		i++;
	if ((i > 4 && argv[i - 1] == ext[2] && argv[i - 2] == ext[1])
		&& (argv[i - 3] == ext[0] && argv[i - 4] == '.'))
		return (0);
	return (1);
}

int		verify_argvs(int argc, char **argv)
{
	if (argc == 3 && extension_check(argv[1], "cub") == 0
		&& my_strcmp(argv[2], "--save") == 0)
	{
		init_game(argv[1], 1);
		return (0);
	}
	else if (argc == 2 && (extension_check(argv[1], "cub") == 0))
	{
		init_game(argv[1], 0);
		return (0);
	}
	else
		return (1);
}
