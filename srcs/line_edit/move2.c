/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:13:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 16:01:35 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line		*moove_first(t_line *cur, int prompt, t_curs *curseur)
{
	check_ynx(curseur, prompt, cur->index);
	check_max(curseur, prompt + full_list_len(cur));
	while (cur->prev)
		cur = moove_left(cur, prompt, curseur);
	return (cur);
}

t_line		*moove_last(t_line *cur, int prompt, t_curs *curseur)
{
	check_ynx(curseur, prompt, cur->index);
	check_max(curseur, prompt + full_list_len(cur));
	while (cur->next)
		cur = moove_right(cur, prompt, curseur);
	return (cur);
}

t_line		*moove_lword(t_line *cur, int prompt, t_curs *curseur)
{
	while (cur->prev && cur->c != ' ')
		cur = moove_left(cur, prompt, curseur);
	while (cur->prev && cur->c == ' ')
		cur = moove_left(cur, prompt, curseur);
	while (cur->prev && cur->prev->c != ' ')
		cur = moove_left(cur, prompt, curseur);
	return (cur);
}

t_line		*moove_rword(t_line *cur, int prompt, t_curs *curseur)
{
	while (cur->next && cur->c != ' ')
		cur = moove_right(cur, prompt, curseur);
	while (cur->next && cur->c == ' ')
		cur = moove_right(cur, prompt, curseur);
	return (cur);
}
