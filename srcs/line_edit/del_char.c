/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:51:33 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/07 15:44:24 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	print_line_del(t_line *current, int len, int check)
{
	tputs(tgetflag("bw"), 0, &ft_inputchar);
	if (!check)
		tputs(tgetstr("le", NULL), 0, &ft_inputchar);
	tputs(tgetstr("dc", NULL), 0, &ft_inputchar);
}

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
		print_line_del(cur, dblist_len(cur), 0);
	}
	return (cur);
}

t_line		*del_next(t_line *cur, int len)
{
	t_line	*del;

	del = cur;
	if (del && del->c != '\0')
	{
		cur = cur->next;
		cur->prev = del->prev;
		if (del->prev)
			del->prev->next = cur;
		del_one_elem(del);
		increment_all(cur, -1);
		print_line_del(cur, dblist_len(cur), 1);
	}
	return (cur);
}
