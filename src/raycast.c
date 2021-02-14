/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:04:42 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:29 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->p.height)
	{
		x = 0;
		while (x < g->p.width)
		{
			g->info.img.data[y * (g->info.img.size_l / 4) \
				+ x] = g->info.buf[y][x];
			x++;
		}
		y++;
	}
	if (g->is_game)
		mlx_put_image_to_window(g->info.mlx, \
				g->info.win, g->info.img.img, 0, 0);
}

void	calc(t_game *g)
{
	int		x;
	t_wall	wall;
	t_sp	sp;

	x = 0;
	while (x < g->p.width)
	{
		calc_walls(x, &wall, g);
		calc_sprite(&sp, g);
		x++;
	}
}

int		main_loop(t_game *g)
{
	calc(g);
	draw(g);
	return (0);
}

void	start_game(t_game *g)
{
	init_info(g);
	load_texture(g);
	mlx_loop_hook(g->info.mlx, &main_loop, g);
	mlx_hook(g->info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, g);
	mlx_loop(g->info.mlx);
}
