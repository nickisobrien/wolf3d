/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:51:09 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/23 21:40:57 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	usage(void)
{
	ft_printf("Usage: \n");
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
