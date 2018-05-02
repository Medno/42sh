/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:12:41 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 16:18:27 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static t_line	*ft_copy(t_line *cur, char c, t_curs *curseur, int checked)
{
	static char	*str;

	if (c == 21)
		cur = select_all(&str, cur, curseur);
	else if (c == 23)
		cur = select_word(&str, cur, curseur);
	else if (c == 25 && !checked)
		cur = paste_selected_line(str, cur, curseur);
	else if (c == 4)
		return (del_next(cur, curseur));
	else if (c == 1)
		return (move_first(cur, curseur));
	else if (c == 2)
		return (move_left(cur, curseur));
	else if (c == 5)
		return (move_last(cur, curseur));
	else if (c == 6)
		return (move_right(cur, curseur));
	return (cur);
}

t_line			*ft_line_usual(t_edit *edit, char c, t_init init)
{
	int		checked;

	check_screen(&edit->curseur);
	checked = last_index(*edit->current) >= edit->curseur.screen.ws_col *
		edit->curseur.screen.ws_row ? 1 : 0;
	if (c == 127 || c == 8)
		return (line_delone(*edit->current, &edit->curseur));
	else if (c == '\t')
		return (completion(edit));
	else if (c == 12)
		return (clearscreen(edit, init));
	else if (c >= 32 && c <= 126 && !checked)
		return (push_new(*edit->current, c, &edit->curseur));
	else
		return (ft_copy(*edit->current, c, &edit->curseur, checked));
}

t_line			*ft_line_esc_2(t_edit *edit, char *buf)
{
	if (ft_strequ(buf, "[1;2B"))
		*edit->current = move_down(*edit->current, &edit->curseur);
	else if (ft_strequ(buf, "[1;2C"))
		*edit->current = move_rword(*edit->current, &edit->curseur);
	else if (ft_strequ(buf, "[1;2D"))
		*edit->current = move_lword(*edit->current, &edit->curseur);
	else if (ft_strequ(buf, "[Z"))
		return (completion_inv(edit));
	edit->comp->reset = 0;
	return (*edit->current);
}

t_line			*ft_line_esc(t_edit *edit)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[A"))
		return (hist_up(*edit->current, edit->histo, edit->prompt_len,
					&edit->curseur));
	else if (ft_strequ(buf, "[B"))
		return (hist_down(*edit->current, edit->histo, edit->prompt_len,
					&edit->curseur));
	else if (ft_strequ(buf, "[C"))
		return (move_right(*edit->current, &edit->curseur));
	else if (ft_strequ(buf, "[D"))
		return (move_left(*edit->current, &edit->curseur));
	else if (ft_strequ(buf, "[H"))
		return (move_first(*edit->current, &edit->curseur));
	else if (ft_strequ(buf, "[F"))
		return (move_last(*edit->current, &edit->curseur));
	else if (ft_strequ(buf, "[3~"))
		return (del_next(*edit->current, &edit->curseur));
	else if (ft_strequ(buf, "[1;2A"))
		return (move_up(*edit->current, &edit->curseur));
	else
		return (ft_line_esc_2(edit, buf));
}
