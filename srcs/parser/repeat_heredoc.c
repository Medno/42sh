/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:55:05 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/14 16:55:31 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*change_str(char *str, char *path)
{
	int		i;
	char	*newstr;

	i = 0;
	while (ft_strncmp(str + i, "<<", 2))
		i++;
	newstr = ft_strndup(str, i);
	i += 2;
	if (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	newstr = ft_strjoindel(newstr, "<");
	newstr = ft_strjoindel(newstr, path);
	newstr = ft_strjoindel(newstr, str + i);
	ft_strdel(&str);
	ft_strdel(&path);
	return (newstr);
}

static int	return_heredoc(t_init *init, char *to_del, char *heredoc)
{
	char	*value;

	value = create_newheredoc(heredoc);
	init->str = change_str(init->str, value);
	ft_strdel(&to_del);
	del_lex(init->lex);
	return (1);
}

int			repeat_heredoc(t_init *init, t_lex *tmp)
{
	char		*line_tmp;
	char		*heredoc;
	static int	checkout = 0;

	if (tmp->token == IO_HERE)
		tmp->value = ft_strjoindel(tmp->value, "\n");
	heredoc = (tmp->token == IO_HERE) ? ft_strdup("") : NULL;
	checkout ? paste_last_hist(&init->historic) : 0;
	while (tmp->token == IO_HERE)
	{
		line_tmp = NULL;
		line_edit(&line_tmp, -1, init);
		if (ft_strequ(line_tmp, tmp->value) || !line_tmp)
			return (return_heredoc(init, line_tmp, heredoc));
		heredoc = (checkout) ? ft_strjoindel(heredoc, "\n") : heredoc;
		checkout = 1;
		heredoc = ft_strnjoindel(heredoc, line_tmp,
				ft_strlen(heredoc) + ft_strlen(line_tmp) - 1);
		ft_strdel(&line_tmp);
	}
	checkout = 0;
	return (0);
}
