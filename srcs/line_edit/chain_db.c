/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_db.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:56:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/07 15:19:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line	*create_elem(char c)
{
	t_line	*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new->c = c;
	new->index = 0;
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

int		dblist_len(t_line *first)
{
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = first;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

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
