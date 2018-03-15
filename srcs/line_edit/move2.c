/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:13:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/15 11:08:33 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line		*move_first(t_line *cur, t_curs *curseur)
{
	check_ynx(curseur, cur->index);
	if (curseur->y > 0 && curseur->x)
		ansi("UP", curseur->y, STDIN_FILENO);
	while (cur->prev)
		cur = cur->prev;
	if (!curseur->x)
	{
		ansi("LE", curseur->screen.ws_col - cur->index, STDIN_FILENO);
		if (curseur->y > 1)
			ansi("UP", curseur->y - 1, STDIN_FILENO);
	}
	else if (curseur->x > cur->index)
		ansi("LE", curseur->x - cur->index, STDIN_FILENO);
	else if (curseur->x < cur->index)
		ansi("RI", cur->index - curseur->x, STDIN_FILENO);
	return (cur);
}

t_line		*move_last(t_line *cur, t_curs *curseur)
{
	check_ynx(curseur, cur->index);
	check_max(curseur, last_index(cur));
	if (curseur->x > curseur->xmax + 1)
		ansi("LE", curseur->x - curseur->xmax - 1, STDIN_FILENO);
	else if (curseur->x < curseur->xmax + 1)
		ansi("RI", curseur->xmax - curseur->x + 1, STDIN_FILENO);
	if (curseur->ymax > curseur->y)
		ansi("DO", curseur->ymax - curseur->y, STDIN_FILENO);
	while (cur->next)
		cur = cur->next;
	return (cur);
}

t_line		*move_lword(t_line *cur, t_curs *curseur)
{
	if (cur->prev)
		cur = move_left(cur, curseur);
	while (cur->prev && (cur->c == ' ' || !cur->c))
		cur = move_left(cur, curseur);
	while (cur->prev && cur->prev->c != ' ')
		cur = move_left(cur, curseur);
	return (cur);
}

t_line		*move_rword(t_line *cur, t_curs *curseur)
{
	while (cur->next && cur->c != ' ' && cur->c != '\n')
		cur = move_right(cur, curseur);
	while (cur->next && (cur->c == ' ' || cur->c == '\n'))
		cur = move_right(cur, curseur);
	return (cur);
}
