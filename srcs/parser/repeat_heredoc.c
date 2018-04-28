/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:55:05 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/14 14:18:41 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*change_str(char *str, char *path, char *token)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (ft_strncmp(str + i, "<<", 2))
		i++;
	newstr = ft_strndup(str, i);
	i += 2;
	if (str[i] && str[i] == ' ')
		i++;
	while (str[i + j] && j < ft_strlen(token) - 1)
		j++;
	newstr = ft_strjoindel(newstr, "<");
	newstr = ft_strjoindel(newstr, path);
	newstr = ft_strjoindel(newstr, str + i + j);
	ft_strdel(&str);
	ft_strdel(&path);
	return (newstr);
}

static int	return_heredoc(t_init *init, char *to_del,
		char *heredoc, char *token)
{
	char	*value;

	value = create_newheredoc(heredoc);
	init->str = change_str(init->str, value, token);
	ft_strdel(&to_del);
	del_lex(init->lex);
	return (1);
}

static int	no_heredoc(t_init *init, char *to_del, char *heredoc)
{
	ft_strdel(&init->str);
	ft_strdel(&heredoc);
	ft_strdel(&to_del);
	del_lex(init->lex);
	return (-1);
}

static void	delete_escape_heredoc(t_lex *lex)
{
	lex->value = delete_esc(lex->value, ft_strlen(lex->value));
	lex->value = ft_strjoindel(lex->value, "\n");
}

int			repeat_heredoc(t_init *init, t_lex *tmp)
{
	int			ret;
	char		*line_tmp;
	char		*heredoc;
	static int	checkout = 0;

	if (tmp->token == IO_HERE)
		delete_escape_heredoc(tmp);
	heredoc = (tmp->token == IO_HERE) ? ft_strdup("") : NULL;
	while (tmp->token == IO_HERE)
	{
		checkout > 1 ? paste_last_hist(&init->historic) : 0;
		line_tmp = NULL;
		ret = line_edit(&line_tmp, -1, init);
		if (ret == 3)
			return (no_heredoc(init, line_tmp, heredoc));
		if (ft_strequ(line_tmp, tmp->value) || !line_tmp)
			return (return_heredoc(init, line_tmp, heredoc, tmp->value));
		heredoc = (checkout) ? ft_strjoindel(heredoc, "\n") : heredoc;
		heredoc = ft_strnjoindel(heredoc, line_tmp,
				ft_strlen(heredoc) + ft_strlen(line_tmp) - 1);
		ft_strdel(&line_tmp);
		checkout += 1;
	}
	checkout = 0;
	return (0);
}
