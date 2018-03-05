/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:13:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/05 13:56:52 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line		*moove_first(t_line *cur, t_curs *curseur)
{
	check_ynx(curseur, cur->index);
	check_max(curseur, last_index(cur));
	while (cur->prev)
		cur = moove_left(cur, curseur);
	return (cur);
}

t_line		*moove_last(t_line *cur, t_curs *curseur)
{
	check_ynx(curseur, cur->index);
	check_max(curseur, last_index(cur));
	while (cur->next)
		cur = moove_right(cur, curseur);
	return (cur);
}

t_line		*moove_lword(t_line *cur, t_curs *curseur)
{
	while (cur->prev && cur->c != ' ' && cur->c != '\n')
		cur = moove_left(cur, curseur);
	while (cur->prev && (cur->c == ' ' || cur->c == '\n'))
		cur = moove_left(cur, curseur);
	while (cur->prev && cur->prev->c != ' ' && cur->prev->c != '\n')
		cur = moove_left(cur, curseur);
	return (cur);
}

t_line		*moove_rword(t_line *cur, t_curs *curseur)
{
	while (cur->next && cur->c != ' ' && cur->c != '\n')
		cur = moove_right(cur, curseur);
	while (cur->next && (cur->c == ' ' || cur->c == '\n'))
		cur = moove_right(cur, curseur);
	return (cur);
}
