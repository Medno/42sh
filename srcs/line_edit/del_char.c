/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:51:33 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/12 11:10:10 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	print_del(t_line *cur, int len)
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
	ansi("SAVE", 0, STDIN_FILENO);
	write(STDIN_FILENO, &buf, i);
	ansi("REST", 0, STDIN_FILENO);
}

t_line		*del_next(t_line *cur, t_curs *curseur)
{
	t_line	*tmp;

	tmp = cur;
	if (tmp && tmp->c)
	{
		cur = cur->next;
		if (tmp->c == '\n')
			increment_all(cur, curseur, tmp->index - cur->index);
		else
			increment_all(cur, curseur, -1);
		cur->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = cur;
		free_one_tline(tmp);
		ansi("CL_END", 0, STDIN_FILENO);
		print_del(cur, last_index(cur) - cur->index);
	}
	return (cur);
}

t_line		*line_delone(t_line *cur, t_curs *curseur)
{
	if (!cur->prev)
		return (cur);
	cur = move_left(cur, curseur);
	return (del_next(cur, curseur));
}
