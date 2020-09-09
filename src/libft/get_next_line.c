#include "../../cub3d.h"

int		ft_errorsofree(char *left)
{
	if (left != NULL)
		free(left);
	return(-1);
}

char	*new_line(char *left, char **line, int ret)
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
		*line = my_strndup(left, i);
	//keep left stock after jump into dst
		if (ret > 0)
			dst = my_substr(left, i + 1, (my_strlen(left) - i));
	}
	free(left);
	return (dst);
}

int		my_get_next_line(int fd, char **line)
{
	static char	*left;
	// if static, left remain for next call
	// if buf size given no need for malloc !!! BIM just do not forget to free
	char		buf[4096];
	int			ret;
	if (fd > 10000 || fd < 0 || !line)
		return(ft_write_error(-1));
	*line = NULL;
	ret = 1;
	while (ret > 0 && (my_strchr(left, '\n') == NULL))
	{
		if((ret = read(fd, buf, 4095)) < 0)
			return (ft_errorsofree(left));
		buf[ret] = '\0';
		left = my_str_join(left, buf);
	}
	left = new_line(left, line, ret);
	if (ret == 0)
		free(left);
	if (ret > 1)
		ret = 1;
	return (ret);
}
