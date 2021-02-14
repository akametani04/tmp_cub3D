/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:40:09 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:13 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = 0;
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	draw_sp(t_sp *sp, t_game *g)
{
	int	color;
	int	y;

	sp->stripe = sp->draw_start_x - 1;
	while (++sp->stripe < sp->draw_end_x)
	{
		sp->tex_x = (int)((sp->stripe - (-sp->sprite_width / 2 + sp->\
		sprite_screen_x)) * g->info.texture[0].size_l / 4 / sp->sprite_width);
		if (sp->transform_y > 0 && sp->stripe > 0 && sp->stripe < g->p.width \
				&& sp->transform_y < g->info.z_buffer[sp->stripe])
		{
			y = sp->draw_start_y - 1;
			while (++y < sp->draw_end_y)
			{
				sp->tex_y = ((((y - sp->v_move_screen) * 256 - g->p.height * \
					128 + sp->sprite_height * 128) * g->info.texture[0].\
					img_height) / sp->sprite_height) / 256;
				color = g->info.texture[0].data[(g->info.texture[0].size_l / \
					4) * sp->tex_y + sp->tex_x];
				if ((color & 0x00FFFFFF) != 0)
					g->info.buf[y][sp->stripe] = color;
			}
		}
	}
}

void	init_sp(t_sp *sp, t_game *g, int i)
{
	sp->sprite_x = g->p.sprite[g->sprite_order[i]].x - g->info.pos_x;
	sp->sprite_y = g->p.sprite[g->sprite_order[i]].y - g->info.pos_y;
	sp->inv_det = 1.0 / (g->info.plane_x * g->info.dir_y - g->info.dir_x * \
			g->info.plane_y);
	sp->transform_x = sp->inv_det * (g->info.dir_y * sp->sprite_x - \
			g->info.dir_x * sp->sprite_y);
	sp->transform_y = sp->inv_det * (-g->info.plane_y * sp->sprite_x + \
			g->info.plane_x * sp->sprite_y);
	sp->sprite_screen_x = (int)((g->p.width / 2) * (1 + sp->transform_x / \
			sp->transform_y));
	sp->v_move_screen = (int)(V_MOVE / sp->transform_y);
	sp->sprite_height = (int)fabs((g->p.height / sp->transform_y) / V_DIV);
	sp->draw_start_y = -sp->sprite_height / 2 + g->p.height / 2 + \
			sp->v_move_screen;
	sp->draw_start_y = (sp->draw_start_y < 0) ? 0 : sp->draw_start_y;
	sp->draw_end_y = sp->sprite_height / 2 + g->p.height / 2 + \
			sp->v_move_screen;
	sp->draw_end_y = sp->draw_end_y >= g->p.height ? g->p.height - 1 : \
			sp->draw_end_y;
	sp->sprite_width = (int)fabs((g->p.height / sp->transform_y) / U_DIV);
	sp->draw_start_x = -sp->sprite_width / 2 + sp->sprite_screen_x;
	sp->draw_start_x = sp->draw_start_x < 0 ? 0 : sp->draw_start_x;
	sp->draw_end_x = sp->sprite_width / 2 + sp->sprite_screen_x;
	sp->draw_end_x = sp->draw_end_x >= g->p.width ? g->p.width - 1 : \
			sp->draw_end_x;
}

void	calc_sprite(t_sp *sp, t_game *g)
{
	int i;

	i = 0;
	while (i < g->p.num_sprites)
	{
		g->sprite_order[i] = i;
		g->sprite_distance[i] = ((g->info.pos_x - g->p.sprite[i].x) * (g->info.\
			pos_x - g->p.sprite[i].x) + (g->info.pos_y - g->p.sprite[i].y) * \
			(g->info.pos_y - g->p.sprite[i].y));
		i++;
	}
	sort_sprites(g->sprite_order, g->sprite_distance, g->p.num_sprites);
	i = 0;
	while (i < g->p.num_sprites)
	{
		init_sp(sp, g, i);
		draw_sp(sp, g);
		i++;
	}
}
