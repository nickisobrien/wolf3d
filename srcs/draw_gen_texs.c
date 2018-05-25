/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gen_texs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:49:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/24 18:18:50 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_gen_texs(t_world *w)
{
	int x;
	double camerax;
	double raydirx;
	double raydiry;

	int32_t texture[8][TEX_WIDTH * TEX_HEIGHT];
	//generate some textures
	for(int x = 0; x < TEX_WIDTH; x++)
		for(int y = 0; y < TEX_HEIGHT; y++)
		{
			int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / TEX_HEIGHT;
			int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
			texture[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); //flat red texture with black cross
			texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][TEX_WIDTH * y + x] = 256 * xorcolor; //xor green
			texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][TEX_WIDTH * y + x] = 65536 * ycolor; //red gradient
			texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	  }


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
		// //get wall number
		int	texnum;
		texnum = w->map.map[mapx][mapy] - 1;

		//calculate value of wallX
		double wallx; //where exactly the wall was hit
		if (side == 0)
			wallx = w->player.posy + perpwalldist * raydiry;
		else
			wallx = w->player.posx + perpwalldist * raydirx;
		wallx -= floor((wallx));

		//x coordinate on the texture
		int texx = (int)(wallx * (double)(TEX_WIDTH));
		if (side == 0 && raydirx > 0)
			texx = TEX_WIDTH - texx - 1;
		if (side == 1 && raydiry < 0)
			texx = TEX_WIDTH - texx - 1;

		// draw the pixels of the stripe as a vertical line
		for(int y = drawstart; y < drawend; y++)
		{
			int d = y * 256 - HEIGHT * 128 + lineheight * 128;  //256 and 128 factors to avoid floats
			// TODO: avoid the division to speed this up
			int texy = ((d * TEX_HEIGHT) / lineheight) / 256;
			uint32_t color = texture[texnum][TEX_HEIGHT * texy + texx];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1)
				color = (color >> 1) & 8355711;
			img_pixel_put(&w->image, x, y, color);
		}
    }
}
