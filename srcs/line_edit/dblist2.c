/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dblist2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:33:03 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 12:22:27 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	increment_all(t_line *current, char c)
{
	t_line	*tmp;

	tmp = current;
	while (tmp)
	{
		tmp->index += c;
		tmp = tmp->next;
	}
}

void	free_dblist(t_line *el)
{
	while (el->prev)
		el = el->prev;
	del_elem(el);
}
