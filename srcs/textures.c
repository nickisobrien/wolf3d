/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 23:20:38 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/23 23:21:17 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	load_textures(t_world *w)
{
	int i;
	char *str;
	static char	*files[] = {"brick.xpm", "grass.xpm", "metal.xpm"};

	i = -1;
	while (++i < TEX_COUNT)
	{
		str = ft_strjoin("./resources/textures/", files[i]);
		if (!(w->texture[i].texture = mlx_xpm_file_to_image(w->mlx, str, &w->texture[i].width, &w->texture[i].height)))
		{
			ft_strdel(&str);
			error("Texture failure");
		}
		if (!(mlx_get_data_addr(&w->texture[i].texture, &w->texture[i].bpp, &w->texture[i].stride, &w->texture[i].endian)))
		{
			ft_strdel(&str);
			error("Texture failure");
		}
		ft_strdel(&str);
	}
}