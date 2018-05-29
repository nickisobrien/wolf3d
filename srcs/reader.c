/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:07:13 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/29 13:47:45 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static int	malloc_map(t_world *w)
{
	int	i;

	if (!(w->map.map = malloc(sizeof(int *) * w->map.rows)))
		error("Malloc error");
	i = -1;
	while (++i < w->map.rows)
		if (!(w->map.map[i] = malloc(sizeof(int) * w->map.cols)))
			error("Malloc error");
	return (-1);
}

static int	set_dimensions(t_world *w)
{
	int		i;
	char	*line;

	ft_get_next_line(w->fd, &line);
	w->map.rows = ft_atoi(line);
	i = -1;
	while (ft_isdigit(line[++i]))
		;
	w->map.cols = ft_atoi(line + i);
	ft_strdel(&line);
	return (malloc_map(w));
}

void		read_map(t_world *w)
{
	char	*line;
	int		i;
	int		j;
	int		counter;

	i = set_dimensions(w);
	while (++i < w->map.rows && ft_get_next_line(w->fd, &line) > 0 && (j = -1))
	{
		counter = 0;
		while (line[++j] && counter < w->map.cols)
		{
			if (ft_isdigit(line[j]))
			{
				w->map.map[i][counter] = ft_atoi(line + j);
				counter++;
			}
			while (ft_isdigit(line[j]))
				j++;
		}
		if (counter != w->map.cols)
			invalid_map();
		ft_strdel(&line);
	}
	if (i != w->map.rows)
		invalid_map();
}
