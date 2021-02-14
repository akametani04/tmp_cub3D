/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:59:59 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:24 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_if_sp_pos(t_game *g, char map_chr, int x, int map_height)
{
	if (map_chr == '2')
	{
		g->p.sprite[g->p.num_sprites].x = x + 0.5;
		g->p.sprite[g->p.num_sprites].y = map_height + 0.5;
		g->p.num_sprites++;
		if (g->p.num_sprites > SP_NUM_MAX)
			error_exit("too many sprite\n");
	}
}

char	validate_chr(char **line)
{
	if (**line == 'N')
		return (P_N);
	if (**line == 'S')
		return (P_S);
	if (**line == 'W')
		return (P_W);
	if (**line == 'E')
		return (P_E);
	if (is_space(**line))
		return (EMP);
	if (**line == '0')
		return (EMP);
	if (**line == '1')
		return (WALL);
	if (**line == '2')
		return (SPRT);
	error_exit("format error in map\n");
	return (0);
}

void	check_if_start_pos(t_game *g, char map_chr, int x, int map_height)
{
	if (map_chr == 'N' || map_chr == 'S' || map_chr == 'W' || map_chr == 'E')
	{
		if (g->p.start_x != -1 || g->p.start_y != -1)
			error_exit("format error in map <start pos not single>\n");
		g->p.start_x = x;
		g->p.start_y = map_height;
		g->p.start_dir = map_chr;
	}
}

void	load_map(char **line, t_game *g, int map_height)
{
	int		x;
	int		line_len;
	char	map_chr;

	x = 0;
	line_len = ft_strlen(*line);
	if (line_len > MAP_WIDTH_MAX)
		error_exit("format error in map <too wide> \n");
	g->p.map_width = fmax(g->p.map_width, line_len);
	while (x < line_len)
	{
		map_chr = validate_chr(line);
		check_if_start_pos(g, map_chr, x, map_height);
		check_if_sp_pos(g, map_chr, x, map_height);
		g->p.w_map[map_height][x] = map_chr;
		x++;
		(*line)++;
	}
	while (x < MAP_WIDTH_MAX)
	{
		g->p.w_map[map_height][x] = OUT;
		x++;
	}
}
