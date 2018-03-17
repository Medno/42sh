/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:40:00 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/17 17:47:51 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	remove_elem(t_path *elem, t_path **orig)
{
	t_path	*tmp;
	t_path	*tmp2;

	tmp = elem->prev;
	tmp2 = elem->next;
	ft_strdel(&elem->s);
	ft_memdel((void **)&elem);
	if (!tmp && !tmp2)
		return ;
	if (!tmp)
	{
		tmp2->prev = NULL;
		*orig = tmp2;
	}
	else if (!tmp2)
		tmp->next = NULL;
	else
	{
		tmp->next = tmp2;
		tmp2->prev = tmp;
	}
}
