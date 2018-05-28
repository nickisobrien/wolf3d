/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_draws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 16:48:58 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/28 16:30:43 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	get_minimap_pos(t_world *w, int *dim, int *xoff, int *yoff)
{
	if (w->map.open)
		*dim = WIDTH > HEIGHT ? HEIGHT * 0.8 : WIDTH * 0.8;
	else
	{
		*dim = MINIMAP_DIM;
		if (*dim < w->map.cols)
			*dim = w->map.cols;
		if (*dim < w->map.rows)
			*dim = w->map.rows;
	}
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
	while (++y < dim && (x = -1))
	{
		while (++x < dim)
		{
			if ((int)(x / (dim / w->map.cols) >= w->map.cols ||
				(int)(y / (dim / w->map.rows)) >= w->map.rows))
				continue ;
			if ((int)w->player.posx == (int)(y / (dim / w->map.rows)) &&
				(int)w->player.posy == (int)(x / (dim / w->map.cols)))
				img_pixel_put(&w->image, x + xoff, dim - y + yoff, 0xf44242);
			else if (w->map.map[(y / (dim / w->map.rows))]
				[x / (dim / w->map.cols)] > 0)
				img_pixel_put(&w->image, x + xoff, dim - y + yoff, 0x424242);
			else
				img_pixel_put(&w->image, x + xoff, dim - y + yoff, 0xffffff);
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
