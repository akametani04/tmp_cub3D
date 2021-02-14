/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akametan <akametan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:55:48 by ykarasaw          #+#    #+#             */
/*   Updated: 2021/02/14 20:01:18 by akametan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_parse(t_parse *p)
{
	free(p->path_to_no_tex);
	free(p->path_to_so_tex);
	free(p->path_to_we_tex);
	free(p->path_to_ea_tex);
}
