/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/22 14:23:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	read_end(char **line, t_line *elm, t_hist **histo)
{
	handle_history_ret(elm, histo);
	*line = line_to_str(elm);
	free_dblist(elm);
	return (1);
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

int			read_line(char **line, t_line **current, int prompt_len, t_hist **histo)
{
	char	c;
	t_curs	curseur;

	if (prompt_len == -1)
		prompt_len = 2;
	init_curs(&curseur, prompt_len);
	while (read(STDIN_FILENO, &c, 1))
	{
		if (((c == '\"' || c == '\'') && !g_quote) || (c == g_quote && g_quote))
			g_quote = (g_quote) ? 0 : c;
		if (c == 4 && !(*current)->next && !(*current)->prev)
			return (0);//HANDLE_CTRLD_exit
		else if (c == 12)
			;//handle clear
		else if (c == '\n')
		{
			(*current) = moove_last((*current), prompt_len, &curseur);
			(*current) = push_new((*current), c, prompt_len, &curseur);
			if (g_quote)
			{
				ft_printf("{tred}>{eoc} ");
				return (read_line(line, current, -1, histo));
			}
			return (read_end(line, (*current), histo));
		}
		else if (c == 14)
			(*current) = hist_down((*current), histo, prompt_len, &curseur);
		else if (c == 16)
			(*current) = hist_up((*current), histo, prompt_len, &curseur);
		else if (c == 27)
			(*current) = ft_line_esc((*current), prompt_len, &curseur, histo);
		else
			(*current) = ft_line_usual((*current), c, prompt_len, &curseur);
	}
	return (0);
}

int			ft_line_edition(char **line, int prompt_len, t_hist **histo)
{
	t_line			*current;

	g_quote = 0;
	current = create_elem(0);
	init_hist(histo);
	if (read_line(line, &current, prompt_len, histo))
		return (1);
	return (0);
}
