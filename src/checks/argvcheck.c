#include "../../cub3d.h"

int		verify_line(t_all *s, char *line)
{
	int	i;

	i = 0;
	write(1, "verify\n", 7);
	skip_spaces(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		s->error.nbr = parse_resolution(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.s, line, &i);
	else if (line[i] == 'W' && line[i+1] == 'E' && line[i + 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i+ 2] == ' ')
		s->error.nbr = parse_texture(s, &s->texture.e, line, &i);
	else if (line[i] == '1')
		s->error.nbr = parse_map(s, line, &i);
	(s->error.nbr < 0 ) ? write_errors(s->error.nbr) : 0;
	return 8;
}

/*int		ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_spaceskip(line, &i);
	if ((line[i] == '1' || s->err.m == 1) && line[i] != '\0')
		s->err.n = ft_map(s, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		s->err.n = ft_res(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.c, line, &i);
	if (ft_spaceskip(line, &i) && s->err.n == 0 && line[i] != '\0')
		return (ft_strerror(-10));
	return (s->err.n < 0 ? ft_strerror(s->err.n) : 0);
}*/

int		parse_cub(t_all *s, char *cub)
{
	int		ret;
	int		fd;
	char	*line;

    //line=NULL;
	if ((fd = open(cub, O_RDONLY)) < 0)
		return (write_errors(-1));
	while ((ret = my_get_next_line(fd, &line)) > 0)
	{
		printf("line res = %s\n", line);
        if (verify_line(s, line) == -1)
			ret = -1;
		free(line);
		line = NULL;
    }
	free(line);
	close(fd);
	if (ret < 0)
		return(write_errors(-2));
    // 	ft_pos(s);
    // 	s->spr = NULL;
    // 	ft_slist(s);
    // 	return (ft_parcheck(s));
    // }
	return 0;
}

int		extensionCheck(char *argv, char *ext)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
		i++;
	if ((i > 4 && argv[i - 1] == ext[2] && argv[i - 2] == ext[1]) && (argv[i - 3] == ext[0] && argv[i - 4] == '.'))
		return (0);
	return (1);
}

int		verify_argvs(int argc, char ** argv)
{
	if (argc == 3 && extensionCheck(argv[1], "cub") == 0 && my_strcmp(argv[2], "--save") == 0)  {
		//initiation de toutes les structures avec enregistrement première image
		init_game(argv[1], 1);
		return 0;
	}
	else if (argc == 2 && (extensionCheck(argv[1], "cub") == 0)) {
		init_game(argv[1], 0);
		return 0;
	}
	else return 1;
}
