/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:46:24 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/27 16:30:45 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	init_player(t_world *w)
{
	w->player.posx = 4;
	w->player.posy = 4;
	w->player.dirx = 0.2;
	w->player.diry = 0.2;
	w->player.planex = 0.0;
	w->player.planey = 0.66;
	w->player.movespeed = 1.0;
	w->player.rotspeed = 0.2;
}

void		place_minimap(t_world *w)
{
	int x;
	int y;
	int dim;
	int xoff;
	int yoff;

	if (!w->map.open)
	{
		dim = MINIMAP_DIM;
		xoff = MINIMAP_OFFSET;
		yoff = MINIMAP_OFFSET;
	}
	else
	{
		dim = WIDTH > HEIGHT ? HEIGHT * 0.8 : WIDTH * 0.8;
		xoff = WIDTH / 2 - dim / 2;
		yoff = HEIGHT / 2 - dim / 2;
	}

	y = -1;
	while (++y < dim)
	{
		x = -1;
		while (++x < dim)
		{
			if ((int)(x / (int)(dim / 24) >= w->map.cols || (int)(y / (int)(dim / 24)) >= w->map.rows))
				continue ;
			if ((int)w->player.posy == (int)(y / (int)(dim / 24)) && (int)w->player.posx == (int)(x / (int)(dim / 24)))
				img_pixel_put(&w->image, x + xoff, y + yoff, 0);
			else if (w->map.map[x / (int)(dim / 24)][(int)(y / (int)(dim / 24))])
				img_pixel_put(&w->image, x + xoff, y + yoff, 0x424242);
			else
				img_pixel_put(&w->image, x + xoff, y + yoff, 0xffffff);
		}
	}
}

static void	init(t_world *w, char *file)
{
	w->mlx = mlx_init();
	w->window = mlx_new_window(w->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	w->mode = 0;
	read_map(w, file);
	init_image(w);
	init_player(w);
	load_textures(w);
	draw_colors(w);
	place_crosshair(w);
	place_minimap(w);
	mlx_put_image_to_window(w->mlx, w->window, w->image.image, 0, 0);
}

int			main(int argc, char **argv)
{
	t_world w;

	if (argc != 2)
		usage();
	init(&w, argv[1]);
	mlx_hook(w.window, 2, 0, key_pressed_hook, &w);
	mlx_hook(w.window, 17, 0, hook_close, &w);
	mlx_loop(w.mlx);
	return (0);
}
