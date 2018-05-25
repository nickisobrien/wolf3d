/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:46:24 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/24 18:19:22 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	init_player(t_world *w)
{
	w->player.posx = 22;
	w->player.posy = 12;
	w->player.dirx = 0.2;
	w->player.diry = 0.2;
	w->player.planex = 0.0;
	w->player.planey = 0.66;
	w->player.movespeed = 1;
	w->player.rotspeed = 0.25;
}

static void	init(t_world *w, char *file)
{
	w->mlx = mlx_init();
	w->window = mlx_new_window(w->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	read_map(w, file);
	init_image(w);
	init_player(w);
	load_textures(w);
	draw_gen_texs(w);
	mlx_put_image_to_window(w->mlx, w->window, w->image.image, 0, 0);
	place_crosshair(w);
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
