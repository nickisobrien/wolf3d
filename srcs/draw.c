/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 19:01:22 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 15:53:00 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

//used for the shared parts of the draws
void	setup_dda(t_world *w, t_draw *d, int x)
{
	d->camerax = 2 * x / (double)WIDTH - 1; //x coord in cam space
	d->raydirx = w->player.dirx + w->player.planex * d->camerax;
	d->raydiry = w->player.diry + w->player.planey * d->camerax;

	//which box of the map we're in
	d->mapx = (int)w->player.posx;
	d->mapy = (int)w->player.posy;

	//length of ray from one x or y-d.side to next x or y-side
	d->deltadistx = fabs(1 / d->raydirx);
	d->deltadisty = fabs(1 / d->raydiry);

	//calculate step and initial sideDist
	if (d->raydirx < 0)
	{
		d->stepx = -1;
		d->sidedistx = (w->player.posx - d->mapx) * d->deltadistx;
	}
	else
	{
		d->stepx = 1;
		d->sidedistx = (d->mapx + 1.0 - w->player.posx) * d->deltadistx;
	}
	if (d->raydiry < 0)
	{
		d->stepy = -1;
		d->sidedisty = (w->player.posy - d->mapy) * d->deltadisty;
	}
	else
	{
		d->stepy = 1;
		d->sidedisty = (d->mapy + 1.0 - w->player.posy) * d->deltadisty;
	}
}

void	perform_dda(t_world *w, t_draw *d)
{
	//perform DDA
	int hit = 0; //was there a wall hit?
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (d->sidedistx < d->sidedisty)
		{
			d->sidedistx += d->deltadistx;
			d->mapx += d->stepx;
			d->side = 0;
		}
		else
		{
			d->sidedisty += d->deltadisty;
			d->mapy += d->stepy;
			d->side = 1;
		}
		//Check if ray has hit a wall
		if (w->map.map[d->mapx][d->mapy] > 0)
			hit = 1;
	}
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (d->side == 0)
		d->perpwalldist = (d->mapx - w->player.posx + (1 - d->stepx) / 2) / d->raydirx;
	else
		d->perpwalldist = (d->mapy - w->player.posy + (1 - d->stepy) / 2) / d->raydiry;
}

void		place_crosshair(t_world *w)
{
	mlx_pixel_put(w->mlx, w->window, WIDTH/2-1, HEIGHT/2, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2-2, HEIGHT/2, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2+1, HEIGHT/2, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2+2, HEIGHT/2, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2, HEIGHT/2-1, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2, HEIGHT/2-2, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2, HEIGHT/2+1, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2, HEIGHT/2+2, 0xffffff);
	mlx_pixel_put(w->mlx, w->window, WIDTH/2, HEIGHT/2, 0xffffff);
}
