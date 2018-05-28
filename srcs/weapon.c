/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 17:03:52 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/27 18:32:40 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	place_crosshair(t_world *w)
{
	img_pixel_put(&w->image, WIDTH / 2 - 1, HEIGHT / 2, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2 - 2, HEIGHT / 2, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2 + 1, HEIGHT / 2, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2 + 2, HEIGHT / 2, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2, HEIGHT / 2 - 1, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2, HEIGHT / 2 - 2, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2, HEIGHT / 2 + 1, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2, HEIGHT / 2 + 2, 0xffffff);
	img_pixel_put(&w->image, WIDTH / 2, HEIGHT / 2, 0xffffff);
}

void		load_weapon(t_world *w)
{
	int			i;
	char		*str;
	static char	*files[5] = {"01.xpm", "02.xpm", "03.xpm", "04.xpm", "05.xpm"};

	i = -1;
	while (++i < 5)
	{
		str = ft_strjoin("./resources/weapon/", files[i]);
		if (!(w->weapon[i].image = mlx_xpm_file_to_image(w->mlx, str,
			&w->weapon[i].width, &w->weapon[i].height)))
		{
			ft_strdel(&str);
			error("Texture failure 1");
		}
		w->weapon[i].ptr = mlx_get_data_addr(w->weapon[i].image,
			&w->weapon[i].bpp, &w->weapon[i].size_line,
			&w->weapon[i].endian);
		w->weapon[i].bpp /= 8;
		ft_strdel(&str);
	}
}

void		place_weapon(t_world *w, int index)
{
	int x;
	int y;
	int xoff;
	int yoff;
	int color;

	xoff = WIDTH / 2 - w->weapon[index].width / 2;
	yoff = HEIGHT - w->weapon[index].height;
	y = -1;
	while (++y < w->weapon[index].height)
	{
		x = -1;
		while (++x < w->weapon[index].width)
		{
			color = get_color(w->weapon[index], y, x);
			if (color)
				img_pixel_put(&w->image, x + xoff, y + yoff, color);
		}
	}
	place_crosshair(w);
}
