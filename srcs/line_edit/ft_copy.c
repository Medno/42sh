/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:51:32 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/14 08:47:43 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line	*paste_selected_line(char *str, t_line *cur, t_curs *curseur)
{
	while (str && *str)
	{
		cur = push_new(cur, *str, curseur);
		str++;
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
	while (cur->prev && (cur->c == ' ' || !cur->c))
		cur = move_left(cur, curseur);
	while (cur->prev && cur->prev->c != ' ')
		cur = move_left(cur, curseur);
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
