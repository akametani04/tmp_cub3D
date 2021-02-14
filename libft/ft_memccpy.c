/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:02:09 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 03:05:06 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *s;

	s = (unsigned char *)src;
	while (n--)
	{
		*(unsigned char *)dst++ = *(unsigned char *)s;
		if (*s++ == (unsigned char)c)
			return (dst);
	}
	return (NULL);
}
