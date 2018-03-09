/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:26:39 by hlely             #+#    #+#             */
/*   Updated: 2018/03/09 14:56:02 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	repeat_line_edition(t_init *init, t_lex *tmp)
{
	char		*line_tmp;
	static int	checkout = 0;

	if (checkout)
		paste_last_hist(&init->historic);
	if ((tmp->token == QUOTE && g_quote) ||
			(tmp->next && tmp->next->token == EOI && (tmp->token == AND_IF
				|| tmp->token == OR_IF || ft_strequ(tmp->value, "|") ||
				tmp->token == DLESSDASH)))
	{
		checkout = 1;
		ft_cfmakeraw(&init->current);
		ft_line_edition(&line_tmp, -1, &init->historic, init->new_env);
		ft_cfmakedefault(&init->current);
		init->str = ft_strjoindel(init->str, line_tmp);
		del_lex(init->lex);
		ft_strdel(&line_tmp);
		return (1);
	}
	checkout = 0;
	return (0);
}

char	*change_str(char *str, char *path)
{
	int		i;
	char	*newstr;

	i = 0;
	while (ft_strncmp(str + i, "<<", 2))
		i++;
	newstr = ft_strndup(str, i);
	i += 2;
	if (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		i++;
	newstr = ft_strjoindel(newstr, "<");
	newstr = ft_strjoindel(newstr, path);
	newstr = ft_strjoindel(newstr, str + i);
	return (newstr);
}

int	repeat_heredoc(t_init *init, t_lex **tmp)
{
	char		*line_tmp;
	char		*tmp_tmp;
	char		*heredoc;
	static int	checkout = 0;

	tmp_tmp = (*tmp)->value;
	if ((*tmp)->token == IO_HERE)
	{
		heredoc = ft_strdup("");
		(*tmp)->value = ft_strjoindel((*tmp)->value, "\n");
	}
	if (checkout)
		paste_last_hist(&init->historic);
	while ((*tmp)->token == IO_HERE)
	{
		ft_cfmakeraw(&init->current);
		ft_line_edition(&line_tmp, -1, &init->historic, init->new_env);
		ft_cfmakedefault(&init->current);
		if (ft_strequ(line_tmp, (*tmp)->value))
		{
			(*tmp)->value = create_newheredoc(heredoc);
			init->str = change_str(init->str, (*tmp)->value);
			ft_strdel(&line_tmp);
			return (1);
		}
		if (checkout)
			heredoc = ft_strjoindel(heredoc, "\n");
		checkout = 1;
		heredoc = ft_strnjoindel(heredoc, line_tmp,
				ft_strlen(heredoc) + ft_strlen(line_tmp) - 1);
		ft_strdel(&line_tmp);
	}
	checkout = 0;
	return (0);
}


int	repeat_line(t_init *init, t_lex *tmp)
{
	if (repeat_heredoc(init, &tmp))
		return (1);
	if (repeat_line_edition(init, tmp))
		return (1);
	return (0);
}
