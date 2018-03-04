/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:12:41 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 14:31:37 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static t_line	*ft_grabb(t_line *cur, char c, int prompt, t_curs *curseur)
{
	static char	*str;
	char		*tmp;

	if (c == 7)
	{
		cur = grab_mod(cur, prompt, curseur);
		str = foo_paste(cur);
		ansi("SAVE", 0, STDIN_FILENO);
		moove_first(cur, curseur);
		ansi("CL_END", 0, STDIN_FILENO);
		tmp = line_to_str(cur);
		write(0, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
		ansi("REST", 0, STDIN_FILENO);
	}
	else if (c == 11)
		cur = paste_line(cur, str, curseur);
	return (cur);
}

t_line			*ft_line_usual(t_edit *edit, char c)
{
	if (c == 127 || c == 8)
		return (line_delone(*edit->current, &edit->curseur));
	else if (c == '\t')// || (c == 4 && !(*(edit->current)->next != NULL)))
		return (completion(edit));
	else if (c == 4)
		return (del_next(*edit->current));
	else if (c == 1)
		return (moove_first(*edit->current, &edit->curseur));
	else if (c == 2)
		return (moove_left(*edit->current, &edit->curseur));
	else if (c == 5)
		return (moove_last(*edit->current, &edit->curseur));
	else if (c == 6)
		return (moove_right(*edit->current, &edit->curseur));
	else if (c >= 32 && c <= 126)
		return (push_new(*edit->current, c, &edit->curseur));
	else
		return (ft_grabb(*edit->current, c, edit->prompt_len, &edit->curseur));
}

t_line		*ft_line_esc_2(t_line *cur, t_curs *curseur, char *buf)
{

	if (ft_strequ(buf, "[1;2B"))
		cur = moove_down(cur, curseur);
	else if (ft_strequ(buf, "[1;2C"))
		cur = moove_rword(cur, curseur);
	else if (ft_strequ(buf, "[1;2D"))
		cur = moove_lword(cur, curseur);
	return (cur);
}

t_line		*ft_line_esc(t_line *cur, int len, t_curs *curseur, t_hist **histo)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[A"))
		return (hist_up(cur, histo, len, curseur));
	else if (ft_strequ(buf, "[B"))
		return (hist_down(cur, histo, len, curseur));
	else if (ft_strequ(buf, "[C"))
		return (moove_right(cur, curseur));
	else if (ft_strequ(buf, "[D"))
		return (moove_left(cur, curseur));
	else if (ft_strequ(buf, "[H"))
		return (moove_first(cur, curseur));
	else if (ft_strequ(buf, "[F"))
		return (moove_last(cur, curseur));
	else if (ft_strequ(buf, "[3~"))
		return (del_next(cur));
	else if (ft_strequ(buf, "[1;2A"))
		return (moove_up(cur, len, curseur));
	else
		return (ft_line_esc_2(cur, curseur, buf));
}
