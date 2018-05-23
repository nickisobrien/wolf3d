/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:12:25 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/22 18:15:52 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WOLF3D_H
# define __WOLF3D_H

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <fcntl.h>

# define WIDTH 770
# define HEIGHT 770
# define WINDOW_NAME "Window"

typedef struct	s_map
{
	int			rows;
	int			cols;
	int			**map;
}				t_map;

typedef struct	s_player
{
	int			x;
	int			y;
	int			direction;
}				t_player;

typedef struct	s_world
{
	t_player	player;
	t_map		map;
	void		*mlx;
	void		*window;
}				t_world;

//hooks
int				key_pressed_hook(int key, t_world *w);
int				hook_close(int key, t_world *w);

//error
void			invalid_map(void);
void			usage(void);
void			error(char *str);

//reader
void			read_map(t_world *w, char *file);

#endif
