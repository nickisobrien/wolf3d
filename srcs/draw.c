/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:49:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/24 12:50:25 by nobrien          ###   ########.fr       */
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
		default:
			return(0xefff1c); //yellow
	}
}

void	draw(t_world *w)
{
	int x;
	double camerax;
	double raydirx;
	double raydiry;

	x = -1;
	while (++x < WIDTH)
	{
		camerax = 2 * x / (double)WIDTH - 1; //x coord in cam space
		raydirx = w->player.dirx + w->player.planex * camerax;
		raydiry = w->player.diry + w->player.planey * camerax;

		//which box of the map we're in
		int mapx = (int)w->player.posx;
		int mapy = (int)w->player.posy;

		//length of ray from current position to next x or y-side
		double sidedistx;
		double sidedisty;

		//length of ray from one x or y-side to next x or y-side
		double deltadistx = fabs(1 / raydirx);
		double deltadisty = fabs(1 / raydiry);
		double perpwalldist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepx;
		int stepy;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (w->player.posx - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - w->player.posx) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (w->player.posy - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - w->player.posy) * deltadisty;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
	        //Check if ray has hit a wall
			if (w->map.map[mapx][mapy] > 0)
				hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpwalldist = (mapx - w->player.posx + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist = (mapy - w->player.posy + (1 - stepy) / 2) / raydiry;

		//Calculate height of line to draw on screen
		int lineheight = (int)(HEIGHT / perpwalldist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawstart = -lineheight / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;

		//choose wall color
		int color = get_wall_color(w, mapx, mapy);

		//give x and y sides different brightness
		if (side == 1)
			color = color / 2;
		vertical_line(w, x, drawstart, drawend, color);
    }
}
