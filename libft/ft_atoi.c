/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 23:46:57 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 03:04:25 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_spaces(const char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||\
				str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
			i++;
		else
			break ;
	}
	return (i);
}

int			ft_atoi(const char *str)
{
	int	ret;
	int i;
	int sign;

	ret = 0;
	i = 0;
	sign = 1;
	i = check_spaces(str, i);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * sign);
}
