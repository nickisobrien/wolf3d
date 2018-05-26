/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:12:25 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 17:03:29 by nobrien          ###   ########.fr       */
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
# define TEX_COUNT 4
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define WINDOW_NAME "Window"

# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14

typedef struct	s_draw
{
	double camerax;
	double raydirx;
	double raydiry;
	int mapx;
	int mapy;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	double sidedistx;
	double sidedisty;
	int side;
	//what direction to step in x or y-direction (either +1 or -1)
	int stepx;
	int stepy;
}				t_draw;

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
	void		*ptr;
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
	int			mode;
	void		*mlx;
	void		*window;
	double		time;
	double		oldtime;
	int			gen_texture[8][TEX_WIDTH * TEX_HEIGHT];
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

//draw general
void			setup_dda(t_world *w, t_draw *d, int x);
void			perform_dda(t_world *w, t_draw *d);
void			place_crosshair(t_world *w);

//draw colors
void			draw_colors(t_world *w);

//draw generated textures
void			draw_gen_texs(t_world *w);
void			init_gen_texs(t_world *w);

//textures
void			load_textures(t_world *w);

#endif
