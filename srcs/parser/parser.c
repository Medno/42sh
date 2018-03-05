/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:27:35 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/05 14:23:14 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir(t_lex *tmp)
{
	if (ft_strequ(tmp->value, ">") || ft_strequ(tmp->value, "<") ||
			tmp->token == GREATAND || tmp->token == LESSAND ||
			tmp->token == DGREAT || tmp->token == DLESS ||
			tmp->token == CLOBBER || tmp->token == DLESSDASH ||
			tmp->token == LESSGREAT)
		return (1);
	return (0);
}

int	check_first(t_lex *first)
{
	if (first->token != WORD && !is_redir(first) && first->token != QUOTE &&
			first->token != IO_NUMBER)
	{
		if (first->token != EOI)
			ft_printf_fd(STDERR_FILENO,
			"42sh: syntax error near unexpected token '%s'\n", first->value);
		del_lex(first);
		return (1);
	}
	return (0);
}

int	err_pars(t_lex *tmp, t_lex *del)
{
	if (is_redir(tmp))
	{
		if (tmp->next && tmp->next->token != WORD)
		{
			ft_printf_fd(STDERR_FILENO,
			"42sh: syntax error near unexpected token '%s'\n", tmp->value);
			del_lex(del);
			return (1);
		}
	}
	if (tmp->next && (tmp->token == AND_IF || tmp->token == OR_IF ||
				ft_strequ(tmp->value, "|") || tmp->token == DLESSDASH ||
				ft_strequ(tmp->value, ";") || tmp->token == DSEMI)
			)
		if ((tmp->next->token != EOI && tmp->next->token != WORD &&
				tmp->next->token != QUOTE) || tmp->token == DSEMI)
		{
			ft_printf_fd(STDERR_FILENO,
			"42sh: syntax error near unexpected token '%s'\n", tmp->value);
			del_lex(del);
			return (1);
		}
	return (0);
}

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
		if ((tmp->token == QUOTE && g_quote))
			init->str = ft_strjoindel(init->str, "\n");
		init->str = ft_strjoindel(init->str, line_tmp);
		del_lex(init->lex);
		ft_strdel(&line_tmp);
		return (1);
	}
	checkout = 0;
	return (0);
}

int	parser(t_init *init)
{
	t_lex	*tmp;
	t_ast	*ast;
	t_cmd	*cmd;

	if (check_first(init->lex))
		return (0);
	tmp = init->lex;
	while (tmp->token != EOI)
	{
		if (err_pars(tmp, init->lex))
			return (0);
		if (repeat_line_edition(init, tmp))
			return (1);
		tmp = tmp->next;
	}
	tmp = init->lex;
	ast = build_ast(tmp);
//	print_ast(ast, NULL);
	cmd = ast_to_struct(ast);
	//print_cmd(cmd);
	//ft_clean_cmd(cmd);
	init->cmd = cmd;
	del_ast(&ast);
	del_lex(init->lex);
	return (0);
}
