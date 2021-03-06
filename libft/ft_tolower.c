/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:33:08 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 03:05:41 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	int diff;

	diff = 'A' - 'a';
	if ('A' <= c && c <= 'Z')
		return (c - diff);
	else
		return (c);
}
