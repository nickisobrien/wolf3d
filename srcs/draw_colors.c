/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:49:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 17:13:26 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void		vertical_line(t_world *w, int x, int drawstart, int drawend, int color)
{
	while (drawstart < drawend)
	{
		img_pixel_put(&w->image, x, drawstart, color);
		drawstart++;
	}
}

static int		get_wall_color(t_world *w, int mapx, int mapy)
{
	int	color;

	color = w->map.map[mapx][mapy];
	if (color == 1)
		return(0xf44242); //red
	else if (color == 2)
		return(0x05af10); //green
	else if (color == 3)
		return(0x0518af); //blue
	else if (color == 4)
		return(0xffffff); //white
	else if (color == 5)
		return(0xf442d7); //pink
	else if (color == 6)
		return(0xf49d41); //orange
	else if (color == 7)
		return(0xa0f441); //lime
	else
		return(0xefff1c); //yellow
}

void	draw_colors(t_world *w)
{
	int x;
	t_draw d;

	x = -1;
	while (++x < WIDTH)
	{
		setup_dda(w, &d, x);
		perform_dda(w, &d);

		//choose wall color
		int color = get_wall_color(w, d.mapx, d.mapy);

		//give x and y sides different brightness
		if (d.side == 1)
			color = color / 2;
		vertical_line(w, x, d.drawstart, d.drawend, color);
    }
}
