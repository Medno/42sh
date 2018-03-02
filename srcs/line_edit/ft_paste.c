/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:28:11 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 14:28:39 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line			*paste_line(t_line *cur, char *str, int prompt,
				t_curs *curseur)
{
	while (str && *str)
	{
		cur = push_new(cur, *str, prompt, curseur);
		str++;
	}
	return (cur);
}

int		count_selected(t_line *cur)
{
	t_line	*tmp;
	int		i;

	tmp = cur;
	i = 0;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->select)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char		*foo_paste(t_line *cur)
{
	t_line		*tmp;
	static char	str[1024];
	int			i;

	if (!count_selected(cur) || count_selected(cur) > 1024)
		return ((char *)&str[0]);
	ft_bzero(str, 1024);
	tmp = cur;
	while (tmp->prev)
		tmp = tmp->prev;
	i = 0;
	while (tmp)
	{
		if (tmp->select)
		{
			str[i] = tmp->c;
			i++;
		}
		tmp = tmp->next;
	}
	str[i] = 0;
	return ((char *)&str[0]);
}
