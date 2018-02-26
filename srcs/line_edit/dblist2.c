/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dblist2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:33:03 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/26 14:23:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*line_to_str(t_line *cur)
{
	char	*str;
	int		i;

	if (!(str = malloc(sizeof(char) * full_list_len(cur) + 1)))
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
