/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:26:39 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 12:20:34 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	condition_repeat(t_lex *tmp)
{
	if ((tmp->token == QUOTE && g_quote) ||
			(tmp->next && tmp->next->token == EOI && (tmp->token == AND_IF
				|| tmp->token == OR_IF || ft_strequ(tmp->value, "|") ||
				tmp->token == DLESSDASH)))
		return (1);
	return (0);
}

static int	repeat_line_edition(t_init *init, t_lex *tmp)
{
	int			ret;
	char		*line_tmp;
	static int	checkout = 0;

	if (checkout)
		paste_last_hist(&init->historic);
	if (condition_repeat(tmp))
	{
		line_tmp = NULL;
		ret = line_edit(&line_tmp, -1, init);
		checkout = (ret == 3 || ret == 1) ? 0 : 1;
		if (!ret)
			init->str = ft_strjoindel(init->str, line_tmp);
		else if (ret == 1 && g_quote == '\\' && (init->stop = 1))
			init->str = delete_esc(init->str, ft_strlen(init->str));
		else if (ret == 1 && g_quote != '\\')
			return (err_eof());
		else if ((ret == 1 && g_quote != '\\') || ret == 3)
			return ((ret == 1 && g_quote != '\\') ? err_eof() : -1);
		del_lex(&init->lex);
		ft_strdel(&line_tmp);
		return (1);
	}
	checkout = 0;
	return (0);
}

void		clean_history_heredoc(t_hist *hist)
{
	char *tmp;
	char *new;

	hist->line = delete_esc(hist->line, ft_strlen(hist->line));
	tmp = ft_strchr(hist->line, '\n');
	new = ft_strsub(hist->line, 0, ft_strlen(hist->line) - ft_strlen(tmp) + 1);
	ft_strdel(&hist->line);
	hist->line = new;
}

int			repeat_line(t_init *init, t_lex *tmp)
{
	int ret;

	ret = repeat_heredoc(init, tmp);
	if (ret)
	{
		clean_history_heredoc(init->historic);
		return (ret);
	}
	ret = repeat_line_edition(init, tmp);
	return (ret);
}
