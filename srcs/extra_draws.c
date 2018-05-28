/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_draws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 16:48:58 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/27 18:48:43 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	get_minimap_pos(t_world *w, int *dim, int *xoff, int *yoff)
{
	if (w->map.open)
		*dim = WIDTH > HEIGHT ? HEIGHT * 0.8 : WIDTH * 0.8;
	else
		*dim = MINIMAP_DIM;
	*xoff = w->map.open ? WIDTH / 2 - *dim / 2 : MINIMAP_OFFSET;
	*yoff = w->map.open ? HEIGHT / 2 - *dim / 2 : MINIMAP_OFFSET;
}

void		place_minimap(t_world *w)
{
	int x;
	int y;
	int dim;
	int xoff;
	int yoff;

	get_minimap_pos(w, &dim, &xoff, &yoff);
	y = -1;
	while (++y < dim)
	{
		x = -1;
		while (++x < dim)
		{
			if ((int)(x / (int)(dim / 24) >= w->map.cols ||
				(int)(y / (int)(dim / 24)) >= w->map.rows))
				continue ;
			if ((int)w->player.posy == (int)(y / (dim / 24)) &&
				(int)w->player.posx == (int)(x / (dim / 24)))
				img_pixel_put(&w->image, x + xoff, y + yoff, 0);
			else if (w->map.map[x / (dim / 24)][(y / (dim / 24))])
				img_pixel_put(&w->image, x + xoff, y + yoff, 0x424242);
			else
				img_pixel_put(&w->image, x + xoff, y + yoff, 0xffffff);
		}
	}
}

void		place_background(t_world *w)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y > HEIGHT / 2)
				img_pixel_put(&w->image, x, y, 0x4581B3);
			else
				img_pixel_put(&w->image, x, y, 0x86CDF9);
		}
	}
}
