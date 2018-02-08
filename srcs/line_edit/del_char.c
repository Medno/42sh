/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:51:33 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/08 11:03:06 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line		*line_delone(t_line *cur, int len)
{
	t_line	*del;

	del = cur->prev;
	if (del)
	{
		cur->prev = del->prev;
		if (del->prev)
			del->prev->next = cur;
		del_one_elem(del);
		increment_all(cur, -1);
		tputs(tgetstr("le", NULL), 0, &ft_inputchar);
		tputs(tgetstr("dc", NULL), 0, &ft_inputchar);
	}
	return (cur);
}

t_line		*del_next(t_line *cur, int len)
{
	t_line	*del;

	del = cur;
	if (del && del->c)
	{
		cur = cur->next;
		cur->prev = del->prev;
		if (del->prev)
			del->prev->next = cur;
		del_one_elem(del);
		increment_all(cur, -1);
		tputs(tgetstr("dc", NULL), 0, &ft_inputchar);
	}
	return (cur);
}
