/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:28:40 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:14 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_side_dist(t_wall *wall, t_game *g)
{
	if (wall->ray_dir_x < 0)
	{
		wall->step_x = -1;
		wall->side_dist_x = (g->info.pos_x - wall->map_x) * \
			wall->delta_dist_x;
	}
	else
	{
		wall->step_x = 1;
		wall->side_dist_x = (wall->map_x + 1.0 - g->info.pos_x)\
			* wall->delta_dist_x;
	}
	if (wall->ray_dir_y < 0)
	{
		wall->step_y = -1;
		wall->side_dist_y = (g->info.pos_y - wall->map_y)\
			* wall->delta_dist_y;
	}
	else
	{
		wall->step_y = 1;
		wall->side_dist_y = (wall->map_y + 1.0 - \
			g->info.pos_y) * wall->delta_dist_y;
	}
}

void	init_wall(int x, t_wall *wall, t_game *g)
{
	wall->camera_x = 2 * x / (double)g->p.width - 1;
	wall->ray_dir_x = g->info.dir_x + g->info.plane_x * wall->camera_x;
	wall->ray_dir_y = g->info.dir_y + g->info.plane_y * wall->camera_x;
	wall->map_x = (int)g->info.pos_x;
	wall->map_y = (int)g->info.pos_y;
	wall->delta_dist_x = fabs(1 / wall->ray_dir_x);
	wall->delta_dist_y = fabs(1 / wall->ray_dir_y);
	wall->perp_wall_dist = 0;
	wall->step_x = 0;
	wall->step_y = 0;
	wall->hit = 0;
	wall->side = 0;
	init_side_dist(wall, g);
}

void	extend_ray(t_wall *wall, t_game *g)
{
	while (wall->hit == 0)
	{
		if (wall->side_dist_x < wall->side_dist_y)
		{
			wall->side_dist_x += wall->delta_dist_x;
			wall->map_x += wall->step_x;
			wall->side = 0;
		}
		else
		{
			wall->side_dist_y += wall->delta_dist_y;
			wall->map_y += wall->step_y;
			wall->side = 1;
		}
		if (g->p.w_map[wall->map_y][wall->map_x] == WALL)
			wall->hit = 1;
	}
	if (wall->side == 0)
		wall->perp_wall_dist = (wall->map_x - g->info.pos_x \
				+ (1 - wall->step_x) / 2) / wall->ray_dir_x;
	else
		wall->perp_wall_dist = (wall->map_y - g->info.pos_y \
				+ (1 - wall->step_y) / 2) / wall->ray_dir_y;
}

void	init_wall2(t_wall *wall, t_game *g)
{
	wall->line_height = (int)(g->p.height / wall->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + g->p.height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + g->p.height / 2;
	if (wall->draw_end >= g->p.height)
		wall->draw_end = g->p.height - 1;
	wall->tex_num = (g->p.w_map[wall->map_y][wall->map_x] != '0') ? 1 : 0;
	if (wall->tex_num)
	{
		if (wall->side == 1 && wall->ray_dir_y < 0)
			wall->tex_num = 1;
		if (wall->side == 1 && wall->ray_dir_y > 0)
			wall->tex_num = 2;
		if (wall->side == 0 && wall->ray_dir_x < 0)
			wall->tex_num = 3;
		if (wall->side == 0 && wall->ray_dir_x > 0)
			wall->tex_num = 4;
	}
}

void	calc_walls(int x, t_wall *wall, t_game *g)
{
	init_wall(x, wall, g);
	extend_ray(wall, g);
	init_wall2(wall, g);
	find_tex_start(wall, g);
	put_color(wall, g, x);
}
