/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:07:13 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/25 18:25:28 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	set_dimensions(t_world *w, char *str)
{
	int	i;

	w->map.rows = ft_atoi(str);
	i = -1;
	while (ft_isdigit(str[++i]))
		;
	w->map.cols = ft_atoi(str + i);
	ft_strdel(&str);
}

static void	malloc_map(t_world *w)
{
	int	i;

	if (!(w->map.map = malloc(sizeof(int *) * w->map.rows)))
		error("Malloc error");
	i = -1;
	while (++i < w->map.rows)
	{
		if (!(w->map.map[i] = malloc(sizeof(int) * w->map.cols)))
			error("Malloc error");
	}
}

void		read_map(t_world *w, char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	int		counter;

	if ((fd = open(file, O_RDONLY)) == -1)
		invalid_map();
	ft_get_next_line(fd, &line);
	set_dimensions(w, line);
	malloc_map(w);
	i = -1;
	while (++i < w->map.rows && ft_get_next_line(fd, &line) > 0)
	{
		if (!line)
			error("Line read error");
		j = -1;
		counter = -1;
		while (line[++j] && counter < w->map.cols)
			if (ft_isdigit(line[j]))
				w->map.map[i][++counter] = line[j] - '0';
		ft_strdel(&line);
	}
}
