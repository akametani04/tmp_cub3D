/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:47:13 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 03:05:12 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		d = (unsigned char *)dst;
		s = (unsigned char *)src;
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d = (unsigned char *)dst + (n - 1);
		s = (unsigned char *)src + (n - 1);
		while (n--)
			*d-- = *s--;
	}
	return (dst);
}
