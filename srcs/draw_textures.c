/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 23:20:38 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 17:39:37 by nobrien          ###   ########.fr       */
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
		if (!(w->texture[i].image = mlx_xpm_file_to_image(w->mlx, str, &w->texture[i].width, &w->texture[i].height)))
		{
			ft_strdel(&str);
			error("Texture failure 1");
		}
		w->texture[i].ptr = mlx_get_data_addr(w->texture[i].image, &w->texture[i].bpp, &w->texture[i].size_line, &w->texture[i].endian);
		w->texture[i].bpp /= 8;
		ft_strdel(&str);
	}
}
