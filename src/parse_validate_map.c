/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:06:04 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:26 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	fill_map(t_game *g, int x, int y)
{
	if (x < 0 || y < 0 || x >= g->p.map_width || y >= g->p.map_height)
		return ;
	if (g->p.w_map[y][x] == WALL || g->p.w_map[y][x] & 4)
		return ;
	if (!(g->p.w_map[y][x] == EMP || g->p.w_map[y][x] == SPRT))
		return ;
	g->p.w_map[y][x] |= 4;
	fill_map(g, x + 1, y);
	fill_map(g, x - 1, y);
	fill_map(g, x, y + 1);
	fill_map(g, x, y - 1);
}

int		check_if_out(t_game *g, int x, int y)
{
	if (x - 1 < 0 || x - 1 < 0 ||\
			x + 1 >= g->p.map_width || y + 1 >= g->p.map_height)
		return (1);
	if (g->p.w_map[y + 1][x] == OUT)
		return (1);
	if (g->p.w_map[y - 1][x] == OUT)
		return (1);
	if (g->p.w_map[y][x + 1] == OUT)
		return (1);
	if (g->p.w_map[y][x - 1] == OUT)
		return (1);
	return (0);
}

int		check_has_hole_unfill(t_game *g)
{
	int	has_hole;
	int	x;
	int y;

	has_hole = 0;
	y = 0;
	while (y < g->p.map_height)
	{
		x = 0;
		while (x < g->p.map_width)
		{
			if (g->p.w_map[y][x] & 4)
			{
				if (check_if_out(g, x, y) == 1)
					has_hole = 1;
				g->p.w_map[y][x] &= ~4;
			}
			x++;
		}
		y++;
	}
	return (has_hole);
}

void	validate_map(t_game *g)
{
	char	tmp;

	tmp = g->p.w_map[g->p.start_y][g->p.start_x];
	g->p.w_map[g->p.start_y][g->p.start_x] = '0';
	fill_map(g, g->p.start_x, g->p.start_y);
	if (check_has_hole_unfill(g))
		error_exit("format error in map <has hole>");
	g->p.w_map[g->p.start_y][g->p.start_x] = tmp;
}
