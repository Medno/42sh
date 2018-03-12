/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:18:23 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/12 15:15:48 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_first(t_lex *first)
{
	if (first->token != WORD && !is_redir(first) && first->token != QUOTE &&
			first->token != IO_NUMBER)
	{
		if (first->token != EOI)
			ft_printf_fd(STDERR_FILENO,
			"42sh: syntax error near unexpected token '%s'\n", first->value);
		return (1);
	}
	return (0);
}

int	err_pars(t_lex *tmp)
{
	if (is_redir(tmp))
		if (tmp->next && (tmp->next->token != WORD &&
					tmp->next->token != IO_HERE))
		{
			ft_printf_fd(STDERR_FILENO,
				"42sh: syntax error near unexpected token '%s'\n", tmp->value);
			return (1);
		}
	if (tmp->next && (tmp->token == AND_IF || tmp->token == OR_IF ||
				ft_strequ(tmp->value, "|") || tmp->token == DLESSDASH ||
				ft_strequ(tmp->value, ";") || tmp->token == DSEMI ||
				tmp->token == DLESS))
		if ((tmp->next->token != EOI && tmp->next->token != WORD &&
					tmp->next->token != QUOTE && tmp->next->token != IO_HERE)
				|| tmp->token == DSEMI)
		{
			ft_printf_fd(STDERR_FILENO,
				"42sh: syntax error near unexpected token '%s'\n", tmp->value);
			return (1);
		}
	return (0);
}

int	err_eof(void)
{
	if (g_quote)
		ft_printf_fd(STDERR_FILENO,
			"42sh: unexpected EOF while looking for matching `%c'\n", g_quote);
	ft_printf_fd(STDERR_FILENO, "42sh: unexpected end of file\n");
	return (-1);
}
