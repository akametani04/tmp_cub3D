/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:03:59 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:05:09 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void		check_arg(int argc, char *argv[])
{
	char	*f_name;
	char	*option;

	f_name = argv[1];
	option = argv[2];
	if (argc < 2 || 3 < argc)
		error_exit("invalid number of argument\n");
	if (!ft_strnstr(f_name, ".cub", ft_strlen(f_name)))
		error_exit("invalid f name\n");
	if (argc == 3 && ft_strncmp(option, "--save", ft_strlen(option)) != 0)
		error_exit("invalid option\n");
}

void		capture_game(t_game *g)
{
	init_info(g);
	load_texture(g);
	calc(g);
	draw(g);
	save_bitmap(g);
	exit(0);
}

void		validate_parse_res(t_game *g)
{
	if (g->p.width == -1 || g->p.height == -1)
		error_exit("parse error\n");
	if (g->p.map_width == -1 || g->p.map_height == -1)
		error_exit("parse error\n");
	if (!g->p.path_to_no_tex || !g->p.path_to_so_tex || \
			!g->p.path_to_we_tex || !g->p.path_to_ea_tex)
		error_exit("parse error\n");
	if (g->p.start_x == -1 || g->p.start_y == -1)
		error_exit("parse error\n");
	if (g->p.f_color.r == -1 || g->p.f_color.g == -1 || g->p.f_color.b == -1)
		error_exit("parse error\n");
	if (g->p.c_color.r == -1 || g->p.c_color.g == -1 || g->p.c_color.b == -1)
		error_exit("parse error\n");
}

int			main(int argc, char *argv[])
{
	t_game	g;

	if (!(g.info.mlx = mlx_init()))
		error_exit("mlx_init error\n");
	mlx_get_screen_size(g.info.mlx, &g.info.max_window_width, \
			&g.info.max_window_height);
	check_arg(argc, argv);
	parse(argv[1], &g);
	validate_parse_res(&g);
	g.is_game = argc == 3 ? 0 : 1;
	if (argc == 3)
		capture_game(&g);
	else
		start_game(&g);
	exit(0);
}
