/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 21:53:08 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*my_strndup(char *s1, int n)
{
	int		i;
	char	*copy;

	i = 0;
	if (!(copy = (char *)malloc(n + 1 * sizeof(char))))
		return (NULL);
	while (i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*my_str_join(char *s1, char *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;
	size_t	totalsize;

	i = 0;
	j = 0;
	totalsize = my_strlen(s1) + my_strlen(s2) + 1;
	if (!(dst = (char *)malloc(totalsize * sizeof(char))))
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	if (s1 != NULL)
		free(s1);
	s1 = NULL;
	s2 = NULL;
	return (dst);
}

char	*my_strchr(char *left, char c)
{
	int	i;

	i = 0;
	if (left == NULL)
		return (NULL);
	while (left[i] != '\0')
	{
		if (left[i] == c)
			return (&left[i + 1]);
		else
			i++;
	}
	if (c == '\0')
		return (&left[i]);
	return (NULL);
}

int		my_strcmp(char *s1, char *s2)
{
	if (s1 && s2)
	{
		while (*s1 == *s2 && *s1 && *s2)
		{
			s1++;
			s2++;
		}
	}
	else
		return (1);
	return (*s1 - *s2);
}

int		my_strlen(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str == NULL)
		return (count);
	else
	{
		while (str[i] != '\0')
		{
			count++;
			i++;
		}
	}
	return (count);
}
