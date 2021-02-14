/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:32:58 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:28 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||\
		c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit(1);
}

void	free_null(char *s)
{
	free(s);
	s = NULL;
}
