/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:51:32 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/12 16:25:13 by kyazdani         ###   ########.fr       */
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
