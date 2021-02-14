#include "../includes/cub.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define _x_EVE_nT_KE_y__pRE_s_s	2
#define _x_EVE_nT_KE_y_E_xIT	17
#define map_width		24
#define map_height		24
#define tex_width 64
#define tex_height 64
#define width 920
#define height 880
#define num_sprites 19

typedef struct	s_img
{
	void	*img;
	int	*data;
	int	size_l;
	int	bpp;
	int	endian;
	int	img_width;
	int	img_height;
}		t_img;

struct _sprite
{
	double	x;
	double	y;
	int	texture;
};

struct _sprite	sprite[num_sprites] =
{
/*	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},
*/
	//row of pillars in front of wall: fisheye test
/*	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},
*/
	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

int	sprite_order[num_sprites];
double	sprite_distance[num_sprites];

typedef struct	s_info
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	void	*mlx;
	void	*win;
	t_img	img;
	int	key_a;
	int	key_w;
	int	key_s;
	int	key_d;
	int	key_esc;
	int	buf[height][width];
	double	z_buffer[width];
	int	**texture;
	double	move_speed;
	double	rot_speed;
}		t_info;

typedef struct	s_pair
{
	double	first;
	int	second;
}		t_pair;

void	key_update(t_info *info);


void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int	i;
	int	j;

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

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

int	worldMap[map_width][map_height] = {
	{1,1,1,1,1,1,1,1,1,1,1,4,4,6,4,4,6,4,6,4,4,4,6,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
	{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
	{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
	{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
	{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
	{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
	{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

void	draw(t_info *info)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			g->info.img.data[y * width + x] = g->info.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->info.mlx, g->info.win, g->info.img.img, 0, 0);
}

void	calc(t_info *info)
{
	int		x;
	s_wall	wall;

	x = 0;
	while (x < width)
	{
		wall.camera_x = 2 * x / (double)width - 1;
		double ray_dir_x = g->info.dir_x + g->info.plane_x * camera_x;
		double ray_dir_y = g->info.dir_y + g->info.plane_y * camera_x;

		int map_x = (int)g->info.pos_x;
		int map_y = (int)g->info.pos_y;

		double side_dist_x;
		double side_dist_y;

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;

		int step_x;
		int step_y;

		int hit = 0;
		int side;

		// initialize
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (g->info.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - g->info.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (g->info.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - g->info.pos_y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (worldMap[map_x][map_y] > 0) hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - g->info.pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - g->info.pos_y + (1 - step_y) / 2) / ray_dir_y;


		// ----------------------		
		// 
		int line_height = (int)(height / perp_wall_dist);

		int draw_start = -line_height / 2 + height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int drawEnd = line_height / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;
		
		int tex_num = worldMap[map_x][map_y];

		double	wall_x;
		if (side == 0)
			wall_x = g->info.pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = g->info.pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= (int)wall_x;

		int	tex_x;
		tex_x = (int)(wall_x * (double)tex_width);
		if (side == 0 && ray_dir_x > 0)
			tex_x = tex_width - tex_x - 1;
		if (side == 1 && ray_dir_x < 0)
			tex_x = tex_width - tex_x - 1;

		double	step;
		double	tex_pos;
		step = 1.0 * tex_height / line_height;
		tex_pos = (draw_start - height / 2 + line_height / 2) * step;

		int	tex_y;
		int	color;
		int	y;
		y = 0;
		while (y <= draw_start)
		{
			g->info.buf[y][x] = 100;
			y++;
		}
		while (y < drawEnd)
		{
			tex_y = (int)tex_pos & (tex_height - 1);
			tex_pos += step;
			color = g->info.texture[tex_num][tex_height * tex_y + tex_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			g->info.buf[y][x] = color;
			y++;
		}
		while (y < height)
		{
			g->info.buf[y][x] = 10000;
			y++;
		}
		g->info.z_buffer[x] = perp_wall_dist;

		//_s_pRITE CA_sTI_nG

		int i;	
		i = 0;
		while (i < num_sprites)
		{
			sprite_order[i] = i;
			sprite_distance[i] = ((g->info.pos_x - sprite[i].x) * (g->info.pos_x - sprite[i].x) + (g->info.pos_y - sprite[i].y) * (g->info.pos_y - sprite[i].y));
			i++;
		}
	sort_sprites(sprite_order, sprite_distance, num_sprites);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < num_sprites; i++)
	{
		//translate sprite position to relative to camera
		double sprite_x = sprite[sprite_order[i]].x - g->info.pos_x;
		double sprite_y = sprite[sprite_order[i]].y - g->info.pos_y;

		//transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
		// [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [                 ]
		// [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

		double inv_det = 1.0 / (g->info.plane_x * g->info.dir_y - g->info.dir_x * g->info.plane_y); //required for correct matrix multiplication

		double transform_x = inv_det * (g->info.dir_y * sprite_x - g->info.dir_x * sprite_y);
		double transform_y = inv_det * (-g->info.plane_y * sprite_x + g->info.plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3_d, the distance of sprite to player, matching sqrt(sprite_distance[i])

		int sprite_screen_x = (int)((width / 2) * (1 + transform_x / transform_y));

		//parameters for scaling and moving the sprites
		#define u_div 1
		#define v_div 1
		#define vMove 0.0
		int vMove_screen = (int)(vMove / transform_y);

		//calculate height of the sprite on screen
		int sprite_height = (int)fabs((height / transform_y) / v_div); //using "transform_y" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int draw_start_y = -sprite_height / 2 + height / 2 + vMove_screen;
		if(draw_start_y < 0) draw_start_y = 0;
		int drawEnd_y = sprite_height / 2 + height / 2 + vMove_screen;
		if(drawEnd_y >= height) drawEnd_y = height - 1;

		//calculate width of the sprite
		int sprite_width = (int)fabs((height / transform_y) / u_div);
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if(draw_start_x < 0) draw_start_x = 0;
		int drawEnd_x = sprite_width / 2 + sprite_screen_x;
		if(drawEnd_x >= width) drawEnd_x = width - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = draw_start_x; stripe < drawEnd_x; stripe++)
		{
			int tex_x = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * tex_width / sprite_width) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transform_y > 0 && stripe > 0 && stripe < width && transform_y < g->info.z_buffer[stripe])
			for(int y = draw_start_y; y < drawEnd_y; y++) //for every pixel of the current stripe
			{
				int d = (y-vMove_screen) * 256 - height * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
				int tex_y = ((d * tex_height) / sprite_height) / 256;
				int color = g->info.texture[sprite[sprite_order[i]].texture][tex_width * tex_y + tex_x]; //get current color from the texture
				if((color & 0x00_f_f_f_f_f_f) != 0) g->info.buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}

		x++;
	}
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == K__w)
	{
		if (!worldMap[(int)(g->info.pos_x + g->info.dir_x * g->info.move_speed)][(int)(g->info.pos_y)])
			g->info.pos_x += g->info.dir_x * g->info.move_speed;
		if (!worldMap[(int)(g->info.pos_x)][(int)(g->info.pos_y + g->info.dir_y * g->info.move_speed)])
			g->info.pos_y += g->info.dir_y * g->info.move_speed;
	}
	if (key == K__s)
	{
		if (!worldMap[(int)(g->info.pos_x + g->info.dir_x * g->info.move_speed)][(int)(g->info.pos_y)])
			g->info.pos_x -= g->info.dir_x * g->info.move_speed;
		if (!worldMap[(int)(g->info.pos_x)][(int)(g->info.pos_y + g->info.dir_y * g->info.move_speed)])
			g->info.pos_y -= g->info.dir_y * g->info.move_speed;
	}
	if (key == K__d)
	{
		double old_dir_x = g->info.dir_x;
		g->info.dir_x = g->info.dir_x * cos(-g->info.rot_speed) - g->info.dir_y * sin(-g->info.rot_speed);
		g->info.dir_y = old_dir_x * sin(-g->info.rot_speed) + g->info.dir_y * cos(-g->info.rot_speed);
		double old_plane_x = g->info.plane_x;
		g->info.plane_x = g->info.plane_x * cos(-g->info.rot_speed) - g->info.plane_y * sin(-g->info.rot_speed);
		g->info.plane_y = old_plane_x * sin(-g->info.rot_speed) + g->info.plane_y * cos(-g->info.rot_speed);
	}
	if (key == K_A)
	{
		double old_dir_x = g->info.dir_x;
		g->info.dir_x = g->info.dir_x * cos(g->info.rot_speed) - g->info.dir_y * sin(g->info.rot_speed);
		g->info.dir_y = old_dir_x * sin(g->info.rot_speed) + g->info.dir_y * cos(g->info.rot_speed);
		double old_plane_x = g->info.plane_x;
		g->info.plane_x = g->info.plane_x * cos(g->info.rot_speed) - g->info.plane_y * sin(g->info.rot_speed);
		g->info.plane_y = old_plane_x * sin(g->info.rot_speed) + g->info.plane_y * cos(g->info.rot_speed);
	}
	if (key == K_E_sC)
		exit(0);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	img->img = mlx_xpm_file_to_image(g->info.mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(g->info.mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, g->info.texture[0], "textures/eagle.xpm", &img);
	load_image(info, g->info.texture[1], "textures/redbrick.xpm", &img);
	load_image(info, g->info.texture[2], "textures/purplestone.xpm", &img);
	load_image(info, g->info.texture[3], "textures/greystone.xpm", &img);
	load_image(info, g->info.texture[4], "textures/bluestone.xpm", &img);
	load_image(info, g->info.texture[5], "textures/mossy.xpm", &img);
	load_image(info, g->info.texture[6], "textures/wood.xpm", &img);
	load_image(info, g->info.texture[7], "textures/colorstone.xpm", &img);
	load_image(info, g->info.texture[8], "textures/barrel.xpm", &img);
	load_image(info, g->info.texture[9], "textures/pillar.xpm", &img);
	load_image(info, g->info.texture[10], "textures/greenlight.xpm", &img);
}

int 	main(void)
{
	t_info	info;
	info.mlx = mlx_init();

	info.pos_x = 22.0;
	info.pos_y = 11.5;
	info.dir_x = -1.0;
	info.dir_y = 0.0;
	info.plane_x = 0.0;
	info.plane_y = 0.66;
	info.key_a = 0;
	info.key_w = 0;
	info.key_s = 0;
	info.key_d = 0;
	info.key_esc = 0;

	
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			info.buf[i][j] = 0;
			j++;
		}
		i++;
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 11)))
		return (-1);
	for (int i = 0; i < 11; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (tex_height * tex_width))))
			return (-1);
	}

	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < tex_height * tex_width)
		{
			info.texture[i][j] = 0;
			j++;
		}
		i++;
	}

	load_texture(&info);
	info.move_speed = 0.05;
	info.rot_speed = 0.05;

	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVE_nT_KEY__pRE_s_s, 1L << 0, &key_press, &info);
	mlx_loop(info.mlx);
}

