/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:51:33 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/09 14:00:07 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	moove_curs(t_line *current, int prompt)
{
	int		tot;
	int		i;
	struct winsize	screen;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &screen);
	tot = prompt + current->index + 1;
	i = -1;
	if (!(tot % screen.ws_col))
	{
		tputs(tgetstr("up", NULL), 0, &ft_inputchar);
		while (++i < screen.ws_col)
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
		write(0, " ", 1);
		tputs(tgetstr("le", NULL), 0, &ft_inputchar);
		tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
	}
	else
	{
		tputs(tgetstr("le", NULL), 0, &ft_inputchar);
		tputs(tgetstr("dc", NULL), 0, &ft_inputchar);
	}
}

void		print_del(t_line *cur, int len)
{
	t_line	*tmp;
	char	buf[len];
	int		i;

	i = 0;
	tmp = cur;
	ft_bzero(buf, len);
	while (tmp->next)
	{
		buf[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	tputs(tgetstr("sc", NULL), 0, &ft_inputchar);
	write(STDIN_FILENO, &buf, i);
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
		if (cur->next)
			tputs(tgetstr("cd", NULL), 0, &ft_inputchar);
		moove_curs(cur, len);
		if (cur->next)
			print_del(cur, dblist_len(cur));
	}
	return (cur);
}

t_line		*del_next(t_line *cur)
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
		tputs(tgetstr("cd", NULL), 0, &ft_inputchar);
		print_del(cur, dblist_len(cur));
	}
	return (cur);
}
