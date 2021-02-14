/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:58:24 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:23 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		parse_r(char **line, t_game *g)
{
	int	i;

	i = 1;
	i = check_delimiter_space(line, ' ', i);
	g->p.width = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	g->p.height = ft_atoi(*line + i);
	i = check_delimiter_space(line, ' ', i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] != '\0')
		error_exit("format error in map <unexpected chr>\n");
	*line += i;
	return (R);
}

int		parse_c(char **line, t_game *g)
{
	int	i;

	i = 1;
	i = check_delimiter_space(line, ' ', i);
	g->p.c_color.r = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	i = check_delimiter_chr(line, ',', i);
	g->p.c_color.g = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	i = check_delimiter_chr(line, ',', i);
	g->p.c_color.b = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] != '\0')
		error_exit("format error in map <unexpected chr>\n");
	*line += i;
	return (C);
}

int		parse_f(char **line, t_game *g)
{
	int	i;

	i = 1;
	i = check_delimiter_space(line, ' ', i);
	g->p.f_color.r = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	i = check_delimiter_chr(line, ',', i);
	g->p.f_color.g = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	i = check_delimiter_chr(line, ',', i);
	g->p.f_color.b = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] != '\0')
		error_exit("format error in map <unexpected chr>\n");
	*line += i;
	return (F);
}

int		parse_path(char **line, t_game *g, int id)
{
	int		i;

	i = (id == SP ? 1 : 2);
	if (ft_strlen(*line) <= (size_t)i + 1)
		error_exit("format error in map <no path>\n");
	i = check_delimiter_space(line, ' ', i);
	if (id == SP)
		g->p.path_to_sp_tex = ft_strdup((char*)*line + i);
	if (id == NO)
		g->p.path_to_no_tex = ft_strdup((char*)*line + i);
	if (id == SO)
		g->p.path_to_so_tex = ft_strdup((char*)*line + i);
	if (id == WE)
		g->p.path_to_we_tex = ft_strdup((char*)*line + i);
	if (id == EA)
		g->p.path_to_ea_tex = ft_strdup((char*)*line + i);
	*line += i + ft_strlen(*line + i);
	return (id);
}

int		load_identifier(char **line, t_game *g)
{
	if (**line == 'R')
		return (parse_r(line, g));
	if (**line == 'F')
		return (parse_f(line, g));
	if (**line == 'C')
		return (parse_c(line, g));
	if (**line == 'N' && (*line)[1] == 'O')
		return (parse_path(line, g, NO));
	if (**line == 'S' && (*line)[1] == 'O')
		return (parse_path(line, g, SO));
	if (**line == 'W' && (*line)[1] == 'E')
		return (parse_path(line, g, WE));
	if (**line == 'E' && (*line)[1] == 'A')
		return (parse_path(line, g, EA));
	if (**line == 'S')
		return (parse_path(line, g, SP));
	if (**line == '\0')
		return (NL);
	return (NO_ID);
}
