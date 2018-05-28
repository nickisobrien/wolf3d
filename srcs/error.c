/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:51:09 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/28 15:49:06 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	usage(void)
{
	ft_printf("Usage: ./wolf3d map.w3d\n");
	exit(0);
}

void	invalid_map(void)
{
	ft_printf("Invalid file\n");
	usage();
}

void	error(char *str)
{
	ft_printf("%s\n", str);
	exit(-1);
}

void	display_controls(void)
{
	ft_printf("Move: WASD\n");
	ft_printf("Toggle Weapon: E\n");
	ft_printf("Toggle Map: TAB\n");
	ft_printf("Toggle Textures: M\n");
}
