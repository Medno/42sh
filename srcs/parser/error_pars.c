/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:18:23 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/03 11:15:24 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			check_first(t_lex *first)
{
	if (!first)
		return (1);
	if (ft_strequ(first->value, "}"))
		return (print_errpars(1, first->value, 0));
	if (ft_strequ(first->value, "()"))
		return (print_errpars(1, ")", 0));
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

static int	check_brack(char *str, size_t len)
{
	int		i;
	int		open;
	char	buf[len];

	i = 0;
	open = 0;
	ft_bzero(buf, len);
	while (str[i])
	{
		if (!open && str[i] == ')')
			return (print_errpars(1, ")", 0));
		if (!open && str[i] == '(')
			open = 1;
		if (open && str[i] == ')')
			open = 0;
		i++;
	}
	return (0);
}

static int	search_brack(char *str)
{
	if (ft_strchr(str, '(') || ft_strchr(str, ')'))
		return (1);
	return (0);
}

int			err_pars(t_lex *tmp)
{
	if (is_redir(tmp))
		if (tmp->next && (tmp->next->token != WORD &&
				tmp->next->token != IO_HERE && tmp->next->token != QUOTE))
			return (print_errpars(1, tmp->value, 0));
	if (search_brack(tmp->value))
		if (check_brack(tmp->value, ft_strlen(tmp->value)))
			return (1);
	if (tmp->next && (tmp->token == AND_IF || tmp->token == OR_IF ||
				ft_strequ(tmp->value, "|") || tmp->token == DLESSDASH ||
				ft_strequ(tmp->value, ";") || tmp->token == DSEMI ||
				tmp->token == DLESS || ft_strequ(tmp->value, "&")))
		if ((tmp->next->token != EOI && tmp->next->token != WORD &&
			tmp->next->token != QUOTE && tmp->next->token != IO_HERE
			&& !ft_strequ(tmp->next->value, ">") &&
			!ft_strequ(tmp->next->value, "<"))
			|| tmp->token == DSEMI)
			return (print_errpars(1, tmp->value, 0));
	return (0);
}

int			err_eof(void)
{
	if (g_quote)
		print_errpars(2, NULL, g_quote);
	ft_printf_fd(STDERR_FILENO, "42sh: syntax error: unexpected end of file\n");
	return (-1);
}
