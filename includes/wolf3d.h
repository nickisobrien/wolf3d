/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:12:25 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/23 23:51:56 by nobrien          ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 720
# define TEX_COUNT 3
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define WINDOW_NAME "Window"

# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14

# define SKY "./resources/textures/sky.xpm"

typedef struct	s_map
{
	int			rows;
	int			cols;
	int			**map;
}				t_map;

typedef struct	s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		movespeed;
	double		rotspeed;
}				t_player;

typedef struct	s_texture
{
	int			width;
	int			height;
	void		*texture;
	int			bpp;
	int			stride;
	int			endian;
}				t_texture;

typedef struct	s_image
{
	void		*image;
	void		*ptr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_world
{
	t_player	player;
	t_map		map;
	t_image		image;
	t_texture	texture[TEX_COUNT];
	t_image		sky;
	void		*mlx;
	void		*window;
	double		time;
	double		oldtime;
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

//image
void			init_image(t_world *w);
void			img_pixel_put(t_image *img, int x, int y, int color);
void			clear_image(t_image *image);

//draw
void			draw(t_world *w);
void			place_crosshair(t_world *w);

//textures
void			load_textures(t_world *w);

#endif
