/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:19:32 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:22 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void		key_ws(int key, t_game *g)
{
	if (key == K_W)
	{
		if (g->p.w_map[(int)(g->info.pos_y)][(int)(g->info.pos_x +\
				g->info.dir_x * g->info.move_speed)] != '1')
			g->info.pos_x += g->info.dir_x * g->info.move_speed;
		if (g->p.w_map[(int)(g->info.pos_y + g->info.dir_y * \
				g->info.move_speed)][(int)(g->info.pos_x)] != '1')
			g->info.pos_y += g->info.dir_y * g->info.move_speed;
	}
	if (key == K_S)
	{
		if (g->p.w_map[(int)(g->info.pos_y)][(int)(g->info.pos_x \
				- g->info.dir_x * g->info.move_speed)] != '1')
			g->info.pos_x -= g->info.dir_x * g->info.move_speed;
		if (g->p.w_map[(int)(g->info.pos_y - g->info.dir_y * \
				g->info.move_speed)][(int)(g->info.pos_x)] != '1')
			g->info.pos_y -= g->info.dir_y * g->info.move_speed;
	}
}

void		key_da(int key, t_game *g)
{
	if (key == K_D)
	{
		if (g->p.w_map[(int)(g->info.pos_y)][(int)(g->info.pos_x \
				+ g->info.plane_x * g->info.move_speed)] != '1')
			g->info.pos_x += g->info.plane_x * g->info.move_speed;
		if (g->p.w_map[(int)(g->info.pos_y + g->info.plane_y *\
				g->info.move_speed)][(int)(g->info.pos_x)] != '1')
			g->info.pos_y += g->info.plane_y * g->info.move_speed;
	}
	if (key == K_A)
	{
		if (g->p.w_map[(int)(g->info.pos_y)][(int)(g->info.pos_x -\
				g->info.plane_x * g->info.move_speed)] != '1')
			g->info.pos_x -= g->info.plane_x * g->info.move_speed;
		if (g->p.w_map[(int)(g->info.pos_y - g->info.plane_y \
				* g->info.move_speed)][(int)(g->info.pos_x)] != '1')
			g->info.pos_y -= g->info.plane_y * g->info.move_speed;
	}
}

void		key_ar_lr(int key, t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;
	int		sign;

	sign = (key == K_AR_R) ? -1 : 1;
	old_dir_x = g->info.dir_x;
	old_plane_x = g->info.plane_x;
	g->info.dir_x = g->info.dir_x * cos(sign * -g->info.rot_speed) \
			- g->info.dir_y * sin(sign * -g->info.rot_speed);
	g->info.dir_y = old_dir_x * sin(sign * -g->info.rot_speed) \
			+ g->info.dir_y * cos(sign * -g->info.rot_speed);
	g->info.plane_x = g->info.plane_x * cos(sign * -g->info.rot_speed) \
			- g->info.plane_y * sin(sign * -g->info.rot_speed);
	g->info.plane_y = old_plane_x * sin(sign * -g->info.rot_speed) \
			+ g->info.plane_y * cos(sign * -g->info.rot_speed);
}

int			key_press(int key, t_game *g)
{
	if (key == K_W || key == K_S)
		key_ws(key, g);
	if (key == K_D || key == K_A)
		key_da(key, g);
	if (key == K_AR_R || key == K_AR_L)
		key_ar_lr(key, g);
	if (key == K_ESC)
		exit(0);
	return (0);
}
