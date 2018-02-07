/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:51:33 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/07 15:04:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	print_line_del(t_line *current, int len)
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
		del->next = NULL;
		del->prev = NULL;
		free(del);
		del = NULL;
		increment_all(cur, -1);
		print_line_del(cur, dblist_len(cur));
	}
	return (cur);
}
