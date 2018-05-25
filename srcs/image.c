/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:45:00 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/24 14:12:49 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	init_image(t_world *w)
{
	w->image.image = mlx_new_image(w->mlx, WIDTH, HEIGHT);
	w->image.ptr = mlx_get_data_addr(w->image.image,
		&w->image.bpp, &w->image.size_line, &w->image.endian);
	w->image.bpp /= 8;
}

void	img_pixel_put(t_image *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(int *)(img->ptr + (int)((y * WIDTH + x) * img->bpp)) = color;
}

void	clear_image(t_image *image)
{
	ft_bzero(image->ptr, WIDTH * HEIGHT * image->bpp);
}
