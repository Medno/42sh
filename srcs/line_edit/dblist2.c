/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dblist2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:33:03 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 11:09:05 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

char	*line_to_str(t_line *cur)
{
	char	*str;
	int		i;

	if (!(str = malloc(sizeof(char) * line_len(cur) + 1)))
		return (NULL);
	i = 0;
	while (cur->prev)
		cur = cur->prev;
	while (cur->next)
	{
		str[i] = cur->c;
		cur = cur->next;
		i++;
	}
	str[i] = 0;
	return (str);
}

void	increment_all(t_line *current, int c)
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

void	ft_clean_edit(t_edit *edit)
{
	if (edit)
	{
		ft_strdel(&(edit->comp->dir));
		ft_strdel(&(edit->comp->str));
		ft_strdel(&(edit->comp->cmd));
		edit->comp->current = NULL;
		if (edit->comp->list)
		{
			ft_clean_lcomp_list(edit->comp->list);
			edit->comp->list = NULL;
		}
		free(edit->comp);
		edit->comp = NULL;
	}
}
