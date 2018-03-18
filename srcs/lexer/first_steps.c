/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:30:13 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/12 17:42:57 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	cat_op(char c, char buf[])
{
	if (ft_strlen(buf) == 3 || buf[0] == '(' || buf[0] == ')')
		return (0);
	if (buf[0] == '<')
	{
		if (buf[1] && buf[1] == '<' && c == '-')
			return (1);
		if (!buf[1])
			if (c == '>' || c == '<' || c == '&')
				return (1);
	}
	if (buf[0] == '>' && !buf[1])
		if (c == '>' || c == '&' || c == '|')
			return (1);
	if (buf[0] == '&' && !buf[1])
		if (c == '&' || c == '<' || c == '>')
			return (1);
	if (buf[0] == ';' && !buf[1] && c == ';')
		return (1);
	if (buf[0] == '|' && !buf[1] && c == '|')
		return (1);
	return (0);
}

t_lex		*already_op(t_lex *new, char *str, int *i, char buf[])
{
	char	read[2];

	read[0] = str[*i];
	read[1] = '\0';
	if (is_op(str[*i], buf) && cat_op(str[*i], buf))
		ft_strcat(buf, read);
	else
	{
		new = put_in_new(new, buf);
		(*i)--;
	}
	return (new);
}

t_lex		*enter_quote(t_lex *new, char *str, int *i, char buf[])
{
	char	read[2];

	read[0] = str[*i];
	read[1] = '\0';
	new->token = WORD;
	if (!g_quote)
		g_quote = str[*i];
	if (new->prev && is_brack(g_quote))
		g_quote = 0;
	ft_strcat(buf, read);
	if ((g_quote == '\"' || g_quote == '\'') && str[*i] == '\\' && str[*i + 1])
	{
		(*i)++;
		read[0] = str[*i];
		ft_strcat(buf, read);
	}
	return (new);
}

t_lex		*new_op(t_lex *new, char *str, int i, char buf[])
{
	char	read[2];

	read[0] = str[i];
	read[1] = '\0';
	if (buf[0])
	{
		if (is_number(buf) && (str[i] == '>' || str[i] == '<'))
			new->token = IO_NUMBER;
		new = put_in_new(new, buf);
	}
	ft_strcat(buf, read);
	new->token = OP;
	return (new);
}

t_lex		*close_new(t_lex *new, char buf[])
{
	if (new->token != NONE)
		new = put_in_new(new, buf);
	return (new);
}
