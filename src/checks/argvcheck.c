#include "../../cub3d.h"

int distribute_line(t_all *s, char *line)
{
	int i;

	i = 0;
	skip_spaces(line, &i); // i++ till no space
	if (line[i] == 'R' && line[i + 1] == ' ')
		s->error.nbr = parse_resolution(s, line, &i); //then send the entire line (with spaces)
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.spr, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->error.nbr = get_color(&s->texture.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->error.nbr = get_color(&s->texture.c, line, &i);
	else if (line[i] == '1' && line[i + 1] != '\0')
		s->error.nbr = parse_map(s, line, &i);
	if (s->error.nbr == 0 && line[i] != '\0')
		return (write_errors(-10));
	return (s->error.nbr < 0 ? write_errors(s->error.nbr) : 0);
}

int parse_cub(t_all *s, char *cub)
{
	int ret;
	int fd;
	char *line;

	line = NULL;
	if ((fd = open(cub, O_RDONLY)) < 0)
		return (write_errors(-1));
	while ((ret = my_get_next_line(fd, &line)) > 0)
	{
		if (distribute_line(s, line) == -1)
			ret = -1;
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	if (ret < 0)
		return (write_errors(-2));
	return (0);
}

int extensionCheck(char *argv, char *ext)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
		i++;
	if ((i > 4 && argv[i - 1] == ext[2] && argv[i - 2] == ext[1]) && (argv[i - 3] == ext[0] && argv[i - 4] == '.'))
		return (0);
	return (1);
}

int verify_argvs(int argc, char **argv)
{
	if (argc == 3 && extensionCheck(argv[1], "cub") == 0 && my_strcmp(argv[2], "--save") == 0)
	{
		//initiation de toutes les structures avec enregistrement première image
		init_game(argv[1], 1);
		return 0;
	}
	else if (argc == 2 && (extensionCheck(argv[1], "cub") == 0))
	{
		init_game(argv[1], 0);
		return 0;
	}
	else
		return 1;
}
