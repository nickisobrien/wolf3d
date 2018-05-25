/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:49:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 15:53:45 by nobrien          ###   ########.fr       */
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
	switch(w->map.map[mapx][mapy])
	{
		case 1:
			return(0xf44242); //red
		case 2:
			return(0x05af10); //green
		case 3:
			return(0x0518af); //blue
		case 4:
			return(0xffffff); //white
		case 5:
			return(0xf442d7); //pink
		case 6:
			return(0xf49d41); //orange
		case 7:
			return(0xa0f441); //lime
		default:
			return(0xefff1c); //yellow
	}
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

		//Calculate height of line to draw on screen
		int lineheight = (int)(HEIGHT / d.perpwalldist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawstart = -lineheight / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;

		//choose wall color
		int color = get_wall_color(w, d.mapx, d.mapy);

		//give x and y sides different brightness
		if (d.side == 1)
			color = color / 2;
		vertical_line(w, x, drawstart, drawend, color);
    }
}
