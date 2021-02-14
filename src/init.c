/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:33:23 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:21 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_id_array(int *ids)
{
	int		i;

	i = START_ID;
	while (i < END_ID + 1)
		ids[i++] = 0;
	return ;
}

void	init_rgb(t_rgb *c)
{
	c->r = -1;
	c->g = -1;
	c->b = -1;
}

void	init_parse(t_parse *p)
{
	int	x;
	int	y;

	y = -1;
	p->width = -1;
	p->height = -1;
	p->map_width = -1;
	p->map_height = -1;
	p->path_to_no_tex = NULL;
	p->path_to_so_tex = NULL;
	p->path_to_we_tex = NULL;
	p->path_to_ea_tex = NULL;
	init_rgb(&p->f_color);
	init_rgb(&p->c_color);
	p->start_x = -1;
	p->start_y = -1;
	p->num_sprites = 0;
	while (++y < MAP_HEIGHT_MAX)
	{
		x = -1;
		while (++x < MAP_WIDTH_MAX)
		{
			p->w_map[y][x] = '\0';
		}
	}
}
