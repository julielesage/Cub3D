#include "cub3d.h"

int		ft_errorsofree(char *buf, char *left)
{
	if (left !== NULL)
		free(left);
	free(buf);
	return(-1);
}

char	new_line(char *left, char **line, int ret)
{
	int		i;
	char	*dst;

	i = 0;
	dst = NULL;
	if (left != NULL)
	//create a line till a jump in *line
	{
		while (left[i] != '\n' && left[i] != '\0')
			i++;
		*line = strndup(left, i);
	//keep left stock after jump into dst
		if (ret > 0)
			dst = ft_substr(left, i + 1, (ft_strlen(left) - i));
	}
	free(left);
	return (dst);
}

int		get_next_line(int fd, char **line)
{
	static char	*left;
	// if static, left remain for next call
	// if buf size given no need for malloc !!! BIM just do not forget to free
	char		buf[4096];
	int			ret;

	if (fd > 10000 || fd < 0 || !(line))
		return(ft_write_error(-1));
	*line = NULL;
	read_size = 1;
	while (ret > 0 && ft_strchr(left, "\n") == NULL)
	{
		if((ret = read(fd, buf, 4095)) < 0)
			return (ft_errorsofree(buf, left);
		buf[ret] = "\0";
		left = str_join(left, buf);
	}
	free(buf);
	left = new_line(left, line, ret);
	if (ret == 0)
		free(left);
	if (ret > 1)
		ret = 1;
	return (ret);
}
