/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:56:45 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/06 16:33:56 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		cat_op(char c, char buf[])
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

t_lex	*all_steps(t_lex *new, char *str, int *i, char buf[])
{
	if (new->token == OP && !g_quote)
		new = already_op(new, str, i, buf);
	else if (is_esc(str[*i]) && !g_quote)
		new = enter_quote(new, str, i, buf);
	else if (!g_quote && is_op(str[*i], buf))
		new = new_op(new, str, *i, buf);
	else if (!g_quote && (str[*i] == '\n' || str[*i] == ' '))
		new = close_new(new, buf);
	else if (new->token == WORD || new->token == QUOTE || str[*i] == g_quote)
		concat_char(str, *i, buf);
	else if (str[*i] == '#')
		while (str[*i] != '\n')
			(*i)++;
	else
		new = new_word(new, str, *i, buf);
	return (new);
}

void	build_lexer(t_lex *first, char *str, int len_str)
{
	int		i;
	char	buf[len_str + 1];
	t_lex	*new;

	i = 0;
	new = first;
	ft_bzero(buf, len_str);
	while (str[i])
	{
		new = all_steps(new, str, &i, buf);
		i++;
	}
	new = end_of_new(new, buf);
}

t_lex	*lexer(char *str)
{
	t_lex	*first;

	if (!str)
		return (NULL);
	first = init_lexer();
	build_lexer(first, str, ft_strlen(str));
	return (first);
}
