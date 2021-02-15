/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#             */
/*   Updated: 2021/01/20 23:08:30 by jlesage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		make_xpm(t_all *s, t_tex *texture, char *file)
{
	int tab[5];

	if (extension_check(file, "xpm") == 1)
		return (-9);
	texture->img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
	if (texture->img == 0 || tab[0] != 64 || tab[1] != 64)
		return (-9);
	texture->adr = (unsigned int *)mlx_get_data_addr(texture->img, &tab[2],
	&tab[3], &tab[4]);
	return (0);
}
