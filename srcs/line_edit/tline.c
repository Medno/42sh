/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 11:29:48 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/19 11:50:46 by kyazdani         ###   ########.fr       */
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
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	free_one_tline(t_line *del)
{
	if (del)
	{
		del->next = NULL;
		del->prev = NULL;
		ft_memdel((void **)&del);
	}
}

void	free_tline(t_line *first)
{
	t_line	*next;

	while (first->prev)
		first = first->prev;
	while (first)
	{
		next = first->next;
		free_one_tline(first);
		first = next;
	}
}

int		full_tline_len(t_line *el)
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
