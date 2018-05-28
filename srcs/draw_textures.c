/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 23:20:38 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/28 16:15:53 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		load_textures(t_world *w)
{
	int			i;
	char		*str;
	static char	*files[TEX_COUNT] = {"brick.xpm", "grass.xpm", "metal.xpm",
	"roots.xpm", "plank.xpm", "pyrite.xpm", "sand.xpm", "sandy.xpm",
	"serpentine.xpm", "slate.xpm", "sulphur.xpm"};

	i = -1;
	while (++i < TEX_COUNT)
	{
		str = ft_strjoin("./resources/textures/", files[i]);
		if (!(w->texture[i].image = mlx_xpm_file_to_image(w->mlx, str,
			&w->texture[i].width, &w->texture[i].height)))
		{
			ft_strdel(&str);
			error("Texture failure 1");
		}
		w->texture[i].ptr = mlx_get_data_addr(w->texture[i].image,
			&w->texture[i].bpp, &w->texture[i].size_line,
			&w->texture[i].endian);
		w->texture[i].bpp /= 8;
		ft_strdel(&str);
	}
}

static void	draw(t_world *w, t_draw *d, int texnum, int texx)
{
	int				c;
	int				texy;
	unsigned int	color;

	while (d->drawstart < d->drawend)
	{
		c = d->drawstart * 256 - HEIGHT * 128 + d->lineheight * 128;
		texy = ((c * TEX_HEIGHT) / d->lineheight) / 256;
		if (texnum >= TEX_COUNT)
			texnum = 1;
		color = get_color(w->texture[texnum], texy, texx);
		if (d->side == 1)
			color = (color >> 1) & 8355711;
		img_pixel_put(&w->image, d->x, d->drawstart, color);
		d->drawstart++;
	}
}

void		draw_textures(t_world *w)
{
	int		x;
	t_draw	d;
	int		texnum;
	int		texx;
	double	wallx;

	x = -1;
	while (++x < WIDTH)
	{
		d.x = x;
		setup_dda(w, &d, x);
		perform_dda(w, &d);
		texnum = w->map.map[d.mapx][d.mapy] - 1;
		if (d.side == 0)
			wallx = w->player.posy + d.perpwalldist * d.raydiry;
		else
			wallx = w->player.posx + d.perpwalldist * d.raydirx;
		wallx -= floor((wallx));
		texx = (int)(wallx * (double)(TEX_WIDTH));
		if (d.side == 0 && d.raydirx > 0)
			texx = TEX_WIDTH - texx - 1;
		if (d.side == 1 && d.raydiry < 0)
			texx = TEX_WIDTH - texx - 1;
		draw(w, &d, texnum, texx);
	}
}
