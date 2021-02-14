/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:36:12 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:20 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_buf(t_game *g)
{
	int i;

	if (!(g->info.texture = (t_img *)ft_calloc(5, sizeof(t_img))))
		error_exit("malloc error\n");
	if (!(g->info.buf = (int **)ft_calloc(g->p.height, sizeof(int *))))
		error_exit("malloc error\n");
	i = 0;
	while (i < g->p.height)
	{
		if (!(g->info.buf[i] = \
				(int *)ft_calloc(g->p.width, sizeof(int))))
			error_exit("malloc error\n");
		i++;
	}
}

void	init_info(t_game *g)
{
	g->info.pos_x = g->p.start_x + 0.5;
	g->info.pos_y = g->p.start_y + 0.5;
	if (g->p.start_dir == 'N' || g->p.start_dir == 'S')
		g->info.dir_x = 0.0;
	else
		g->info.dir_x = g->p.start_dir == 'E' ? 1.0 : -1.0;
	if (g->p.start_dir == 'W' || g->p.start_dir == 'E')
		g->info.dir_y = 0.0;
	else
		g->info.dir_y = g->p.start_dir == 'N' ? -1.0 : 1.0;
	g->info.plane_x = (g->info.dir_x != 0.0) ? 0 : g->info.dir_y * -0.66;
	g->info.plane_y = (g->info.dir_y != 0.0) ? 0 : g->info.dir_x * 0.66;
	init_buf(g);
	if (g->is_game)
		if (!(g->info.win = mlx_new_window(g->info.mlx, g->p.width\
						, g->p.height, "mlx")))
			error_exit("mlx_new_window error");
	g->info.move_speed = 0.05;
	g->info.rot_speed = 0.05;
	g->info.img.img = mlx_new_image(g->info.mlx, g->p.width, g->p.height);
	g->info.img.data = (int *)mlx_get_data_addr(g->info.img.img, \
		&g->info.img.bpp, &g->info.img.size_l, &g->info.img.endian);
}

void	load_image(t_game *g, t_img *texture, char *path, int tex_num)
{
	t_img	img;

	if ((img.img = mlx_xpm_file_to_image(g->info.mlx, path, \
			&img.img_width, &img.img_height)) == NULL)
		error_exit("error in load image1\n");
	if (!(img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, \
			&img.size_l, &img.endian)))
		error_exit("error in load image2\n");
	texture[tex_num] = img;
}

void	load_texture(t_game *g)
{
	load_image(g, g->info.texture, g->p.path_to_sp_tex, 0);
	load_image(g, g->info.texture, g->p.path_to_no_tex, 1);
	load_image(g, g->info.texture, g->p.path_to_so_tex, 2);
	load_image(g, g->info.texture, g->p.path_to_we_tex, 3);
	load_image(g, g->info.texture, g->p.path_to_ea_tex, 4);
}
