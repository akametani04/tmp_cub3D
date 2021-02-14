/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:40:23 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:27 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		check_idcomp(int ids[END_ID + 1])
{
	int	i;
	int	cmp;

	i = R;
	cmp = 1;
	while (i < END_ID + 1)
	{
		if (ids[i] != 1)
			cmp = 0;
		if (ids[i] > 1)
			error_exit("format error in map <dup elem>\n");
		i++;
	}
	if (cmp)
		return (1);
	return (0);
}

void	validate_figures(t_game *g, int id)
{
	if (id == R)
	{
		if (g->p.width <= 0 || g->p.height <= 0)
			error_exit("format error in map <invalid R>\n");
		if (g->p.width > g->info.max_window_width)
			g->p.width = g->info.max_window_width;
		if (g->p.height > g->info.max_window_height)
			g->p.height = g->info.max_window_height;
	}
	if (id == C)
	{
		if (g->p.c_color.r < 0 || g->p.c_color.g < 0 || g->p.c_color.b < 0)
			error_exit("format error in map <negative c color>\n");
		if (g->p.c_color.r > 255 || g->p.c_color.g > 255 \
				|| g->p.c_color.b > 255)
			error_exit("format error in map <invalid c color>\n");
	}
	if (id == F)
	{
		if (g->p.f_color.r < 0 || g->p.f_color.g < 0 || g->p.f_color.b < 0)
			error_exit("format error in map <negative f color>\n");
		if (g->p.f_color.r > 255 || g->p.f_color.g > 255 || \
				g->p.f_color.b > 255)
			error_exit("format error in map <invalid f color>\n");
	}
}

int		read_l_check_id_comp(char **line, t_game *g, int ids[END_ID + 1])
{
	int		id;
	int		idcomp;

	idcomp = 0;
	while (**line)
	{
		if (!(idcomp = check_idcomp(ids)))
			while (is_space(**line))
				(*line)++;
		id = load_identifier(line, g);
		if (id == R || id == F || id == C)
			validate_figures(g, id);
		idcomp = check_idcomp(ids);
		if (idcomp)
		{
			if (id == NO_ID)
				return (1);
			else
				error_exit("format error <id / new line in wrong place>\n");
		}
		else if (id == NO_ID)
			error_exit("format error <wrong chr though id not comp>\n");
		ids[id]++;
	}
	return (0);
}

void	add_map_last_line(t_game *g, int map_height, int ids[END_ID + 1])
{
	int x;

	if (!(check_idcomp(ids)))
		error_exit("format error in map <elem not enough>\n");
	x = 0;
	while (x < MAP_WIDTH_MAX)
	{
		g->p.w_map[map_height][x] = OUT;
		x++;
	}
	g->p.map_height = map_height;
	validate_map(g);
}

void	parse(char *f_name, t_game *g)
{
	int			fd;
	char		*line;
	int			ids[END_ID + 1];
	int			map_height;
	char		*tmp;

	fd = 0;
	map_height = 0;
	init_parse(&g->p);
	init_id_array(ids);
	if ((fd = open(f_name, O_RDONLY)) > 0)
	{
		while ((get_next_line(fd, (char**)&line)) > 0)
		{
			if (map_height > MAP_HEIGHT_MAX)
				error_exit("format error in map <too high>\n");
			tmp = line;
			if (read_l_check_id_comp(&line, g, ids))
				load_map(&line, g, map_height++);
			free_null(tmp);
		}
		free_null(line);
		add_map_last_line(g, map_height++, ids);
	}
	close(fd);
}
