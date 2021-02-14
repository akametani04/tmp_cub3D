/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:19:02 by akametan          #+#    #+#             */
/*   Updated: 2021/02/14 19:42:44 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# if defined(__APPLE__)
#  include "../minilibx_mms_20200219/mlx.h"
#  include "key_macos.h"
# else
#  include "../minilibx_linux/mlx.h"
#  include "key_linux.h"
# endif

# include <errno.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# define MAP_WIDTH_MAX 512
# define MAP_HEIGHT_MAX 512
# define WIN_WIDTH_MAX 3000
# define WIN_HEIGHT_MAX 3000
# define SP_NUM_MAX 5
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define P_N 'N'
# define P_S 'S'
# define P_W 'W'
# define P_E 'E'
# define OUT 'x'
# define EMP '0'
# define WALL '1'
# define SPRT '2'
# define NO_ID 0
# define START_ID 10
# define NL 10
# define R 11
# define SP 12
# define NO 13
# define SO 14
# define WE 15
# define EA 16
# define F 17
# define C 18
# define END_ID 18
# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

typedef struct	s_key
{
	int			a;
	int			d;
	int			s;
	int			w;
	int			esc;
}				t_key;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_wall
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			color;
}				t_wall;

typedef struct	s_s
{
	double		x;
	double		y;
}				t_s;

typedef struct	s_sp
{
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			v_move_screen;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	int			tex_x;
	int			tex_y;
}				t_sp;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef struct	s_parse
{
	int			width;
	int			height;
	int			map_width;
	int			map_height;
	char		*path_to_no_tex;
	char		*path_to_so_tex;
	char		*path_to_we_tex;
	char		*path_to_ea_tex;
	char		*path_to_sp_tex;
	t_rgb		f_color;
	t_rgb		c_color;
	int			start_x;
	int			start_y;
	char		start_dir;
	char		w_map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
	int			num_sprites;
	t_s			sprite[SP_NUM_MAX];
}				t_parse;

typedef struct	s_info
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*win;
	int			max_window_width;
	int			max_window_height;
	t_img		img;
	t_key		key;
	int			**buf;
	double		z_buffer[WIN_WIDTH_MAX];
	t_img		*texture;
	int			north_with;
	double		move_speed;
	double		rot_speed;
}				t_info;

typedef struct	s_game
{
	t_parse		p;
	t_info		info;
	int			sprite_order[SP_NUM_MAX];
	double		sprite_distance[SP_NUM_MAX];
	int			is_game;
}				t_game;

void			init_id_array(int *ids);
void			init_parse(t_parse *p);
void			parse(char *f_name, t_game *g);
int				load_identifier(char **line, t_game *g);
void			load_map(char **line, t_game *g, int map_height);
void			validate_map(t_game *g);
void			free_null(char *s);
void			out_parse(t_game *g);
int				is_space(char c);
int				check_delimiter_space(char **line, char c, int i);
int				check_delimiter_chr(char **line, char c, int i);
void			free_parse(t_parse *p);
void			start_game(t_game *g);
void			calc(t_game *g);
void			draw(t_game *g);
void			init_info(t_game *g);
void			load_texture(t_game *g);
void			calc_walls(int x, t_wall *wall, t_game *g);
int				rgb_init(int red, int green, int blue);
void			find_tex_start(t_wall *wall, t_game *g);
void			put_color(t_wall *wall, t_game *g, int x);
void			calc_sprite(t_sp *sp, t_game *g);
int				key_press(int key, t_game *g);
void			save_bitmap(t_game *g);
void			error_exit(char *message);
#endif
