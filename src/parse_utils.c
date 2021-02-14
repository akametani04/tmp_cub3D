/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:46:39 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:25 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		check_delimiter_space(char **line, char c, int i)
{
	if ((*line)[i] != c)
		error_exit("format error in map <delimiter>\n");
	else
	{
		while (is_space((*line)[i]))
		{
			i++;
			if ((*line)[i] != c)
				return (i);
		}
	}
	printf("%s\n", *line);
	error_exit("format error in map <only space>\n");
	return (i);
}

int		check_delimiter_chr(char **line, char c, int i)
{
	if ((*line)[i] != c)
		error_exit("format error in map <delimiter>\n");
	else
		i++;
	return (i);
}
