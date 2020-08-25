#include "cub3d.h"

int	verify_line(t_all s, char **line)
{

}

int ft_parse_cub(t_all s, char *cub)
{
	int		ret;
	int		fd;
	char	*line;

    //line=NULL;
	if ((fd = open(cub, O_RONLY) < 0)
		return (ft_write_error(-1));
	while (ret = get_next_line(fd, &line) > 0)
	{
        if (verify_line(s, line) == -1)
			ret = -1;
		free(line);
		line = NULL;
    }
	free(line);
	close(fd);
	if (ret < 0)
		return(ft_write_error(-2));
    // 	ft_pos(s);
    // 	s->spr = NULL;
    // 	ft_slist(s);
    // 	return (ft_parcheck(s));
    // }

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
