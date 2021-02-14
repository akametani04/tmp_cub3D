/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:59:19 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:11 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

#define BMP_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40
#define BMP_BPP 4
#define BMP_NUM_PLANES 1

void		ft_itoc(unsigned char *s, int i)
{
	s[0] = (unsigned char)(i);
	s[1] = (unsigned char)(i >> 8);
	s[2] = (unsigned char)(i >> 16);
	s[3] = (unsigned char)(i >> 24);
}

void		write_header(int fd, t_game *g)
{
	unsigned char	header[54];
	int				filesize;

	filesize = BMP_HEADER_SIZE + DIB_HEADER_SIZE +
		(BMP_BPP * g->p.width * g->p.height);
	ft_memset(header, 0, 54);
	ft_memcpy(header, "BM", 2);
	ft_itoc(header + 2, filesize);
	header[10] = (unsigned char)(BMP_HEADER_SIZE + DIB_HEADER_SIZE);
	header[14] = (unsigned char)DIB_HEADER_SIZE;
	ft_itoc(header + 18, g->p.width);
	ft_itoc(header + 22, g->p.height);
	header[26] = (unsigned char)BMP_NUM_PLANES;
	header[28] = (unsigned int)(BMP_BPP * 8);
	write(fd, header, BMP_HEADER_SIZE + DIB_HEADER_SIZE);
}

void		write_pixels(int fd, t_game *g)
{
	int				row;
	int				col;
	int				row_size;
	int				padding;

	row = g->p.height - 1;
	row_size = (32 * g->p.width / 32) * 4;
	padding = (row_size % 4) == 0 ? 0 : 4 - (row_size % 4);
	while (row >= 0)
	{
		col = 0;
		while (col < g->p.width)
		{
			write(fd, &g->info.img.data[row * g->p.width + col], BMP_BPP);
			write(fd, "\0\0\0", padding);
			col++;
		}
		row--;
	}
}

void		save_bitmap(t_game *g)
{
	int		fd;

	if ((fd = open("capture.bmp", O_CREAT | O_RDWR, 0666)) == -1)
		error_exit("eroor in opening bmp file\n");
	write_header(fd, g);
	write_pixels(fd, g);
	close(fd);
}
