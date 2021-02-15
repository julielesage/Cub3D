/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 22:00:58 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*new_line(char *left, char **line, int ret)
{
	int		i;
	char	*dst;

	i = 0;
	dst = NULL;
	if (left != NULL)
	{
		while (left[i] != '\n' && left[i] != '\0')
			i++;
		*line = my_strndup(left, i);
		if (ret > 0)
			dst = my_substr(left, i + 1, (my_strlen(left) - i));
	}
	free(left);
	return (dst);
}

int		my_get_next_line(t_all *s, int fd, char **line)
{
	static char	*left;
	char		buf[4096];
	int			ret;

	if (fd > 10000 || fd < 0)
		return (write_errors(s, -20));
	*line = NULL;
	ret = 1;
	while (ret > 0 && (my_strchr(left, '\n') == NULL))
	{
		if ((ret = read(fd, buf, 4095)) < 0)
			free(left);
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
