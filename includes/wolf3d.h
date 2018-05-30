/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:12:25 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/29 12:59:01 by nobrien          ###   ########.fr       */
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
# define TEX_COUNT 11
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MINIMAP_DIM 128
# define MINIMAP_OFFSET 32
# define WINDOW_NAME "Window"

# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14
# define TAB 48
# define M 46
# define E 14
# define ESC 53
# define UP 126
# define LEFT 123
# define DOWN 125
# define RIGHT 124

typedef struct	s_draw
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	double		sidedistx;
	double		sidedisty;
	int			side;
	int			stepx;
	int			stepy;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			x;
}				t_draw;

typedef struct	s_map
{
	int			open;
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
	int			weapon;
}				t_player;

typedef struct	s_image
{
	int			width;
	int			height;
	void		*image;
	char		*ptr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_world
{
	t_player	player;
	t_map		map;
	t_image		image;
	t_image		texture[TEX_COUNT];
	t_image		weapon[5];
	int			mode;
	void		*mlx;
	void		*window;
	int			gen_texture[8][TEX_WIDTH * TEX_HEIGHT];
	int			fd;
}				t_world;
/*
** main
*/
void			draw_calls(t_world *w);

/*
** hooks
*/
int				key_pressed_hook(int key, t_world *w);
int				hook_close(int key, t_world *w);

/*
** error
*/
void			invalid_map(void);
void			usage(void);
void			error(char *str);
void			display_controls(void);

/*
** reader
*/
void			read_map(t_world *w);

/*
** image
*/
void			init_image(t_world *w);
void			img_pixel_put(t_image *img, int x, int y, int color);
void			clear_image(t_image *image);

/*
** draw general
*/
void			setup_dda(t_world *w, t_draw *d, int x);
void			perform_dda(t_world *w, t_draw *d);

/*
** extra draws
*/
void			place_minimap(t_world *w);
void			place_background(t_world *w);

/*
** draw colors
*/
void			draw_colors(t_world *w);

/*
** draw textures
*/
void			draw_textures(t_world *w);
void			load_textures(t_world *w);

/*
** helpers
*/
unsigned int	get_color(t_image texture, int texy, int texx);

/*
** weapon
*/
void			place_weapon(t_world *w, int index);
void			load_weapon(t_world *w);
void			run_weapon_animation(t_world *w);

#endif
