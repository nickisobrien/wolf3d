/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 17:02:51 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/27 17:41:53 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

unsigned int	get_color(t_image texture, int texy, int texx)
{
	char			*ptr;
	unsigned int	color;

	texx %= texture.width;
	texy %= texture.height;
	color = 0;
	ptr = texture.ptr;
	ptr += texy * texture.size_line + texx * texture.bpp;
	if (texy < texture.height && texx < texture.width)
	{
		color += (ptr[2] & 0xFF) << 16;
		color += (ptr[1] & 0xFF) << 8;
		color += *ptr;
	}
	return (color);
}
