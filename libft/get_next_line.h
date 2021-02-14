/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 09:59:02 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 03:05:49 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif
# include <stdlib.h>

size_t	ft_strlen(char *s);
char	*ft_strndup(char *s, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, char c);
int		get_next_line(int fd, char **line);
#endif
