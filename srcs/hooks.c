/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:26:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/27 18:28:28 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	more_keys(int key, t_world *w)
{
	if (key == M)
	{
		w->mode++;
		if (w->mode > 1)
			w->mode = 0;
	}
	if (key == S)
	{
		if (!w->map.map[(int)(w->player.posx - w->player.dirx *
			w->player.movespeed)][(int)(w->player.posy)])
			w->player.posx -= w->player.dirx * w->player.movespeed;
		if (!w->map.map[(int)(w->player.posx)][(int)(w->player.posy -
			w->player.diry * w->player.movespeed)])
			w->player.posy -= w->player.diry * w->player.movespeed;
	}
	if (key == W)
	{
		if (!w->map.map[(int)(w->player.posx + w->player.dirx *
			w->player.movespeed)][(int)(w->player.posy)])
			w->player.posx += w->player.dirx * w->player.movespeed;
		if (!w->map.map[(int)(w->player.posx)][(int)(w->player.posy +
			w->player.diry * w->player.movespeed)])
			w->player.posy += w->player.diry * w->player.movespeed;
	}
}

static void	more_keys2(int key, t_world *w)
{
	double	olddirx;
	double	oldplanex;
	double	mult;

	mult = 0;
	if (key == A)
		mult = -1;
	else if (key == D)
		mult = 1;
	if (mult)
	{
		olddirx = w->player.dirx;
		w->player.dirx = w->player.dirx * cos(w->player.rotspeed * mult) -
		w->player.diry * sin(w->player.rotspeed * mult);
		w->player.diry = olddirx * sin(w->player.rotspeed * mult) +
		w->player.diry * cos(w->player.rotspeed * mult);
		oldplanex = w->player.planex;
		w->player.planex = w->player.planex * cos(w->player.rotspeed * mult) -
		w->player.planey * sin(w->player.rotspeed * mult);
		w->player.planey = oldplanex * sin(w->player.rotspeed * mult) +
		w->player.planey * cos(w->player.rotspeed * mult);
	}
}

int			key_pressed_hook(int key, t_world *w)
{
	more_keys(key, w);
	more_keys2(key, w);
	if (key == TAB)
	{
		if (w->map.open)
			w->map.open = 0;
		else
			w->map.open = 1;
	}
	if (key == E)
	{
		if (w->player.weapon == 1)
			w->player.weapon = 0;
		else
			w->player.weapon = 1;
	}
	if (key == ESC)
		exit(0);
	draw_calls(w);
	return (0);
}

int			hook_close(int key, t_world *w)
{
	(void)key;
	(void)w;
	exit(0);
	return (0);
}
