/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:26:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/23 18:29:26 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

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

int			key_pressed_hook(int key, t_world *w)
{
	if (key == S)
	{
		if (!w->map.map[(int)(w->player.posx - w->player.dirx * w->player.movespeed)][(int)(w->player.posy)])
			w->player.posx -= w->player.dirx * w->player.movespeed;
		if (!w->map.map[(int)(w->player.posx)][(int)(w->player.posy - w->player.diry * w->player.movespeed)])
			w->player.posy -= w->player.diry * w->player.movespeed;
	}
	if (key == W)
	{
		if (!w->map.map[(int)(w->player.posx + w->player.dirx * w->player.movespeed)][(int)(w->player.posy)])
			w->player.posx += w->player.dirx * w->player.movespeed;
		if (!w->map.map[(int)(w->player.posx)][(int)(w->player.posy + w->player.diry * w->player.movespeed)])
			w->player.posy += w->player.diry * w->player.movespeed;
	}
	if (key == A)
	{
		//both camera direction and camera plane must be rotated
		double olddirx = w->player.dirx;
		w->player.dirx = w->player.dirx * cos(-w->player.rotspeed) - w->player.diry * sin(-w->player.rotspeed);
		w->player.diry = olddirx * sin(-w->player.rotspeed) + w->player.diry * cos(-w->player.rotspeed);
		double oldplanex = w->player.planex;
		w->player.planex = w->player.planex * cos(-w->player.rotspeed) - w->player.planey * sin(-w->player.rotspeed);
		w->player.planey = oldplanex * sin(-w->player.rotspeed) + w->player.planey * cos(-w->player.rotspeed);
	}
	if (key == D)
	{
		//both camera direction and camera plane must be rotated
		double olddirx = w->player.dirx;
		w->player.dirx = w->player.dirx * cos(w->player.rotspeed) - w->player.diry * sin(w->player.rotspeed);
		w->player.diry = olddirx * sin(w->player.rotspeed) + w->player.diry * cos(w->player.rotspeed);
		double oldplanex = w->player.planex;
		w->player.planex = w->player.planex * cos(w->player.rotspeed) - w->player.planey * sin(w->player.rotspeed);
		w->player.planey = oldplanex * sin(w->player.rotspeed) + w->player.planey * cos(w->player.rotspeed);
	}
	if (key == 53)
		exit(0);
	clear_image(&w->image);
	draw(w);
	mlx_put_image_to_window(w->mlx, w->window, w->image.image, 0, 0);
	place_crosshair(w);
	return (0);
}

int			hook_close(int key, t_world *w)
{
	(void)key;
	(void)w;
	exit(0);
	return (0);
}
