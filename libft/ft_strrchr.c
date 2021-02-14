/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:13:20 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 03:05:38 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	slen;

	slen = ft_strlen(s) + 1;
	while (slen--)
		if (s[slen] == c)
			return ((char *)&s[slen]);
	return (NULL);
}
