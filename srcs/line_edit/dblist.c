/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dblist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:56:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/06 15:39:18 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line	*create_elem(char c, int len)
{
	t_line	*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new->c = c;
	new->index = len;
	new->select = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	del_one_elem(t_line *del)
{
	if (del)
	{
		del->next = NULL;
		del->prev = NULL;
		free(del);
		del = NULL;
	}
}

void	del_elem(t_line *first)
{
	t_line	*next;

	while (first)
	{
		next = first->next;
		del_one_elem(first);
		first = next;
	}
}

int		line_len(t_line *el)
{
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = el;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int		last_index(t_line *el)
{
	t_line	*tmp;

	tmp = el;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->index);
}
