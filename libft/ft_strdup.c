/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:35:34 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 03:05:24 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	slen;
	char	*ret;

	slen = ft_strlen(s1);
	ret = (char*)malloc(sizeof(char) * slen + 1);
	if (ret == NULL)
		return (NULL);
	ret = (char*)ft_memcpy(ret, s1, slen + 1);
	return (ret);
}
