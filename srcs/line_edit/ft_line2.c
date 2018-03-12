/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:12:41 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/12 15:21:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static t_line	*ft_copy(t_line *cur, char c, t_curs *curseur)
{
	static char	*str;

	if (c == 21)
		cur = select_all(&str, cur, curseur);
	else if (c == 23)
		;
	else if (c == 11)
		cur = paste_selected_line(str, cur, curseur);
	return (cur);
}

t_line			*ft_line_usual(t_edit *edit, char c)
{
	if (c == 127 || c == 8)
		return (line_delone(*edit->current, &edit->curseur));
	else if (c == '\t')
		return (completion(edit));
	else if (c == 4)
		return (del_next(*edit->current, &edit->curseur));
	else if (c == 1)
		return (move_first(*edit->current, &edit->curseur));
	else if (c == 2)
		return (move_left(*edit->current, &edit->curseur));
	else if (c == 5)
		return (move_last(*edit->current, &edit->curseur));
	else if (c == 6)
		return (move_right(*edit->current, &edit->curseur));
	else if (c == 12)
		return (clearscreen(edit));
	else if (c >= 32 && c <= 126)
		return (push_new(*edit->current, c, &edit->curseur));
	else
		return (ft_copy(*edit->current, c, &edit->curseur));
}

t_line			*ft_line_esc_2(t_line *cur, t_curs *curseur, char *buf)
{
	if (ft_strequ(buf, "[1;2B"))
		cur = move_down(cur, curseur);
	else if (ft_strequ(buf, "[1;2C"))
		cur = move_rword(cur, curseur);
	else if (ft_strequ(buf, "[1;2D"))
		cur = move_lword(cur, curseur);
	return (cur);
}

t_line			*ft_line_esc(t_line *cur, int len, t_curs *curseur,
				t_hist **histo)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[A"))
		return (hist_up(cur, histo, len, curseur));
	else if (ft_strequ(buf, "[B"))
		return (hist_down(cur, histo, len, curseur));
	else if (ft_strequ(buf, "[C"))
		return (move_right(cur, curseur));
	else if (ft_strequ(buf, "[D"))
		return (move_left(cur, curseur));
	else if (ft_strequ(buf, "[H"))
		return (move_first(cur, curseur));
	else if (ft_strequ(buf, "[F"))
		return (move_last(cur, curseur));
	else if (ft_strequ(buf, "[3~"))
		return (del_next(cur, curseur));
	else if (ft_strequ(buf, "[1;2A"))
		return (move_up(cur, curseur));
	else
		return (ft_line_esc_2(cur, curseur, buf));
}
