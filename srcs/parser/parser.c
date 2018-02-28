/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:27:35 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/28 15:22:20 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	err_pars(t_lex *tmp)
{
	if (ft_strequ(tmp->value, ">") || ft_strequ(tmp->value, "<") ||
			ft_strequ(tmp->value, ">&") || ft_strequ(tmp->value, "<&") ||
			tmp->token == DGREAT || tmp->token == DLESS ||
			tmp->token == CLOBBER)
	{
		if (tmp->next && tmp->next->token != WORD)
			return (1);
	}
	if (tmp->next && (tmp->token == AND_IF || tmp->token == OR_IF ||
			ft_strequ(tmp->value, "|")))
		if (tmp->next->token != EOI && tmp->next->token != WORD &&
				tmp->next->token != QUOTE)
			return (1);
	return (0);
}

int	parser(t_lex *first, t_hist **histo, char **line, struct termios cur)
{
	t_lex	*tmp;
	t_ast	*ast;
	int		build;
	char	*line_tmp;

	build = 1;
			print_lex(first);
	if (first->token != WORD && !ft_strequ(first->value, ">") && 
			!ft_strequ(first->value, "<") && first->token != DLESS
			&& first->token != DGREAT && first->token != CLOBBER &&
			first->token != LESSGREAT)
	{
		if (first->token != EOI)
			ft_putendl("syntax error");
		build = 0;
	}
	tmp = first;
	while (tmp->token != EOI && build)
	{
		if (err_pars(tmp))
		{
			ft_putendl("syntax error");
			build = 0;
		}
		if ((tmp->token == QUOTE && g_quote) || 
				(tmp->next && tmp->next->token == EOI && (tmp->token == AND_IF
				|| tmp->token == OR_IF || ft_strequ(tmp->value, "|"))))
		{
			ft_cfmakeraw(&cur);
			ft_line_edition(&line_tmp, -1, histo);
			ft_cfmakedefault(&cur);
			if ((tmp->token == QUOTE && g_quote))
				*line = ft_strjoindel(*line, "\n");
			*line = ft_strjoindel(*line, line_tmp);
			del_lex(first);
			return (1);
		}
		tmp = tmp->next;
	}
	if (build)
	{
		tmp = first;
		ast = build_ast(tmp);
		print_ast(ast, NULL);
		del_ast(&ast);
	}
	del_lex(first);
	return (0);
}
