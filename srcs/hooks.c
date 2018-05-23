/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:26:28 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/22 16:51:31 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int			key_pressed_hook(int key, t_world *w)
{
	(void)w;
	if (key == 53)
		exit(0);
	return (0);
}

int			hook_close(int key, t_world *w)
{
	(void)key;
	(void)w;
	exit(0);
	return (0);
}
