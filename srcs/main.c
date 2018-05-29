/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:46:24 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/28 17:44:17 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	get_player_pos(t_world *w)
{
	int x;
	int y;

	y = -1;
	while (++y < w->map.rows)
	{
		x = -1;
		while (++x < w->map.cols)
		{
			if (!w->map.map[y][x])
			{
				w->player.posx = x + 0.5;
				w->player.posy = y + 0.5;
				return ;
			}
		}
	}
	error("No starting position for player");
}

static void	init_player(t_world *w)
{
	get_player_pos(w);
	w->player.dirx = 0.2;
	w->player.diry = 0.2;
	w->player.planex = 0.0;
	w->player.planey = 0.66;
	w->player.movespeed = 1.0;
	w->player.rotspeed = 0.2;
	w->player.weapon = 0;
}

static void	init(t_world *w, char *file)
{
	(void)file;
	w->mlx = mlx_init();
	w->window = mlx_new_window(w->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	w->mode = 0;
	read_map(w, file);
	init_image(w);
	init_player(w);
	load_textures(w);
	load_weapon(w);
	place_background(w);
	draw_calls(w);
	display_controls();
}

void		draw_calls(t_world *w)
{
	clear_image(&w->image);
	place_background(w);
	if (!w->mode)
		draw_colors(w);
	else if (w->mode == 1)
		draw_textures(w);
	if (w->player.weapon)
		place_weapon(w, 0);
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
