/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:51:32 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/15 15:04:09 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line	*paste_selected_line(char *str, t_line *cur, t_curs *curseur)
{
	int		a;
	int		b;

	a = curseur->screen.ws_col * curseur->screen.ws_row;
	b = last_index(cur);
	while (str && *str && b < a)
	{
		cur = push_new(cur, *str, curseur);
		str++;
		b++;
	}
	return (cur);
}

t_line	*select_word(char **str, t_line *cur, t_curs *curseur)
{
	int		len;
	t_line	*save;
	char	*tmp;

	save = cur;
	if (!cur->prev && !cur->next && !cur->c)
		return (cur);
	cur = move_lword(cur, curseur);
	len = save->index - cur->index;
	if (!(tmp = ft_strnew(len)))
		return (cur);
	len = 0;
	while (cur != save)
	{
		tmp[len] = cur->c;
		cur = del_next(cur, curseur);
		len++;
	}
	ft_strdel(str);
	*str = tmp;
	return (cur);
}

t_line	*select_all(char **str, t_line *cur, t_curs *curseur)
{
	int		first;
	char	*tmp;

	tmp = NULL;
	cur = move_first(cur, curseur);
	first = cur->index;
	if (!(tmp = line_to_str(cur)))
		return (cur);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_strdel(str);
	*str = tmp;
	free_tline(cur);
	cur = create_elem(0, first);
	return (cur);
}
