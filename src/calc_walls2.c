/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_walls2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:28:40 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 23:57:56 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		rgb_init(int red, int green, int blue)
{
	int		rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

void	put_color(t_wall *wall, t_game *g, int x)
{
	int		y;

	y = -1;
	while (++y <= wall->draw_start)
	{
		g->info.buf[y][x] = \
			rgb_init(g->p.c_color.r, g->p.c_color.g, g->p.c_color.b);
	}
	while (y < wall->draw_end)
	{
		wall->tex_y = fmin((int)wall->tex_pos, (\
					g->info.texture[wall->tex_num].img_height - 1));
		wall->tex_pos += wall->step;
		wall->color = g->info.texture[wall->tex_num].data[(g->info.\
				texture[wall->tex_num].size_l / 4) * wall->tex_y + wall->tex_x];
		g->info.buf[y][x] = wall->color;
		y++;
	}
	while (y < g->p.height)
	{
		g->info.buf[y][x] = rgb_init(g->p.f_color.r, g->\
			p.f_color.g, g->p.f_color.b);
		y++;
	}
	g->info.z_buffer[x] = wall->perp_wall_dist;
}

void	find_tex_start(t_wall *wall, t_game *g)
{
	if (wall->side == 0)
		wall->wall_x = g->info.pos_y + wall->perp_wall_dist * wall->ray_dir_y;
	else
		wall->wall_x = g->info.pos_x + wall->perp_wall_dist * wall->ray_dir_x;
	wall->wall_x -= (int)wall->wall_x;
	wall->tex_x = (int)(wall->wall_x \
			* (double)(g->info.texture[wall->tex_num].size_l / 4));
	if (wall->side == 0 && wall->ray_dir_x < 0)
		wall->tex_x = (g->info.texture[\
				wall->tex_num].size_l / 4) - wall->tex_x - 1;
	if (wall->side == 1 && wall->ray_dir_y > 0)
		wall->tex_x = (g->info.texture[\
				wall->tex_num].size_l / 4) - wall->tex_x - 1;
	wall->step = 1.0 * g->info.texture[\
				wall->tex_num].img_height / wall->line_height;
	wall->tex_pos = (wall->draw_start - \
			g->p.height / 2 + wall->line_height / 2) * wall->step;
}
