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
		moove_first(cur, prompt, curseur);
		ansi("CL_END", 0, STDIN_FILENO);
		tmp = line_to_str(cur);
		write(0, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
		ansi("REST", 0, STDIN_FILENO);
	}
	else if (c == 11)
		cur = paste_line(cur, str, prompt, curseur);
	return (cur);
}

t_line			*ft_line_usual(t_edit *edit, char c)
{
	if (c == 127 || c == 8)
		return (*edit->current = line_delone(*edit->current, edit->prompt_len,
				&edit->curseur));
	else if (c == '\t')// || (c == 4 && !(*(edit->current)->next != NULL)))
		return (*edit->current = completion(edit));
	else if (c == 4)
		return (*edit->current = del_next(*edit->current));
	else if (c == 1)
		return (*edit->current = moove_first(*edit->current, edit->prompt_len,
				&edit->curseur));
	else if (c == 2)
		return (*edit->current = moove_left(*edit->current, edit->prompt_len,
				&edit->curseur));
	else if (c == 5)
		return (*edit->current = moove_last(*edit->current, edit->prompt_len,
				&edit->curseur));
	else if (c == 6)
		return (*edit->current = moove_right(*edit->current, edit->prompt_len,
				&edit->curseur));
	else if (c >= 32 && c <= 126)
		return (*edit->current = push_new(*edit->current, c, edit->prompt_len,
				&edit->curseur));
	else
		return (*edit->current = ft_grabb(*edit->current, c, edit->prompt_len,
				&edit->curseur));
}

t_line		*ft_line_esc_2(t_line *cur, int prompt, t_curs *curseur, char *buf)
{
	if (ft_strequ(buf, "[1;2A"))
		cur = moove_up(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2B"))
		cur = moove_down(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2C"))
		cur = moove_rword(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2D"))
		cur = moove_lword(cur, prompt, curseur);
	return (cur);
}

t_line		*ft_line_esc(t_line *cur, int len, t_curs *curseur, t_hist **histo)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[A"))
		cur = hist_up(cur, histo, len, curseur);
	else if (ft_strequ(buf, "[B"))
		cur = hist_down(cur, histo, len, curseur);
	else if (ft_strequ(buf, "[C"))
		cur = moove_right(cur, len, curseur);
	else if (ft_strequ(buf, "[D"))
		cur = moove_left(cur, len, curseur);
	else if (ft_strequ(buf, "[H"))
		cur = moove_first(cur, len, curseur);
	else if (ft_strequ(buf, "[F"))
		cur = moove_last(cur, len, curseur);
	else if (ft_strequ(buf, "[3~"))
		cur = del_next(cur);
	else
		cur = ft_line_esc_2(cur, len, curseur, buf);
	return (cur);
}
