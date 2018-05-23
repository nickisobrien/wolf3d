/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:46:24 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/22 18:15:48 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	init(t_world *w, char *file)
{
	w->mlx = mlx_init();
	w->window = mlx_new_window(w->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	mlx_hook(w->window, 2, 0, key_pressed_hook, &w);
	mlx_hook(w->window, 17, 0, hook_close, &w);
	read_map(w, file);
}

int			main(int argc, char **argv)
{
	t_world w;

	if (argc != 2)
		usage();
	init(&w, argv[1]);
	mlx_loop(w.mlx);
	return (0);
}
