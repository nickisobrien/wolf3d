/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:49:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 17:59:23 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	vertical_line(t_world *w, int x, int drawstart, int drawend, int color)
{
	while (drawstart < drawend)
	{
		img_pixel_put(&w->image, x, drawstart, color);
		drawstart++;
	}
}

static int	get_wall_color(t_world *w, int mapx, int mapy)
{
	int	color;

	color = w->map.map[mapx][mapy];
	if (color == 1)
		return (0xf44242);
	else if (color == 2)
		return (0x05af10);
	else if (color == 3)
		return (0x0518af);
	else if (color == 4)
		return (0xffffff);
	else if (color == 5)
		return (0xf442d7);
	else if (color == 6)
		return (0xf49d41);
	else if (color == 7)
		return (0xa0f441);
	else
		return (0xefff1c);
}

void		draw_colors(t_world *w)
{
	int		x;
	int		color;
	t_draw	d;

	x = -1;
	while (++x < WIDTH)
	{
		setup_dda(w, &d, x);
		perform_dda(w, &d);
		color = get_wall_color(w, d.mapx, d.mapy);
		if (d.side == 1)
			color = color / 2;
		vertical_line(w, x, d.drawstart, d.drawend, color);
    }
}
