/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gen_texs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:49:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 17:04:38 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	init_gen_texs(t_world *w)
{
	int x;
	int y;
	//generate some textures
	x = -1;
	while (++x < TEX_WIDTH)
	{
		y = -1;
		while (++y < TEX_HEIGHT)
		{
			int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			int ycolor = y * 256 / TEX_HEIGHT;
			int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
			w->gen_texture[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); //flat red texture with black cross
			w->gen_texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			w->gen_texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			w->gen_texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			w->gen_texture[4][TEX_WIDTH * y + x] = 256 * xorcolor; //xor green
			w->gen_texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			w->gen_texture[6][TEX_WIDTH * y + x] = 65536 * ycolor; //red gradient
			w->gen_texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
}

void	draw_gen_texs(t_world *w)
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
		// //get wall number
		int	texnum;
		texnum = w->map.map[d.mapx][d.mapy] - 1;

		//calculate value of wallX
		double wallx; //where exactly the wall was hit
		if (d.side == 0)
			wallx = w->player.posy + d.perpwalldist * d.raydiry;
		else
			wallx = w->player.posx + d.perpwalldist * d.raydirx;
		wallx -= floor((wallx));

		//x coordinate on the texture
		int texx = (int)(wallx * (double)(TEX_WIDTH));
		if (d.side == 0 && d.raydirx > 0)
			texx = TEX_WIDTH - texx - 1;
		if (d.side == 1 && d.raydiry < 0)
			texx = TEX_WIDTH - texx - 1;

		// draw the pixels of the stripe as a vertical line
		for(int y = drawstart; y < drawend; y++)
		{
			int c = y * 256 - HEIGHT * 128 + lineheight * 128;  //256 and 128 factors to avoid floats
			// TODO: avoid the division to speed this up
			int texy = ((c * TEX_HEIGHT) / lineheight) / 256;
			uint32_t color = w->gen_texture[texnum][TEX_HEIGHT * texy + texx];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (d.side == 1)
				color = (color >> 1) & 8355711;
			img_pixel_put(&w->image, x, y, color);
		}
    }
}
