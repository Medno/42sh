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
	t_line	*tmp;
	char	buf[len];
	int		i;

	ft_bzero(buf, len);
	i = 0;
	tmp = current;
	while (tmp)
	{
		buf[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	if (!check)
		tputs(tgetstr("le", NULL), 0, &ft_inputchar);
	tputs(tgetstr("sc", NULL), 0, &ft_inputchar);
	write(STDIN_FILENO, &buf, len);
	write(STDIN_FILENO, " ", 1);
	tputs(tgetstr("rc", NULL), 0, &ft_inputchar);
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
