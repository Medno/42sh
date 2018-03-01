/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:56:45 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/01 18:44:32 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
	if (buf[0] == '&' && !buf[1] && c == '&')
		return (1);
	if (buf[0] == ';' && !buf[1] && c == ';')
		return (1);
	if (buf[0] == '|' && !buf[1] && c == '|')
		return (1);
	return (0);
}

t_lex	*categorize_op(t_lex *new)
{
	if (ft_strequ("&&", new->value))
		new->token = AND_IF;
	else if (ft_strequ("||", new->value))
		new->token = OR_IF;
	else if (ft_strequ(";;", new->value))
		new->token = DSEMI;
	else if (ft_strequ("<<", new->value))
		new->token = DLESS;
	else if (ft_strequ(">>", new->value))
		new->token = DGREAT;
	else if (ft_strequ("<&", new->value))
		new->token = LESSAND;
	else if (ft_strequ(">&", new->value))
		new->token = GREATAND;
	else if (ft_strequ("<>", new->value))
		new->token = LESSGREAT;
	else if (ft_strequ("<<-", new->value))
		new->token = DLESSDASH;
	else if (ft_strequ(">|", new->value))
		new->token = CLOBBER;
	return (new);
}

t_lex	*categorize_token(t_lex *new)
{
	if (new->token == OP)
		new = categorize_op(new);
	else if (!new->value)
		new->token = EOI;
	else if (ft_strequ("\n", new->value))
		new->token = NEWLINE;
	if (new->token == WORD && g_quote)
		new->token = QUOTE;
	else if (new->token == QUOTE && !g_quote)
		new->token = WORD;
	return (new);
}

t_lex	*put_in_new(t_lex *new, char buf[], int len_str)
{
	new->value = ft_strdup(buf);
	new = categorize_token(new);
	ft_bzero(buf, len_str);
	new->next = init_lexer();
	new->next->prev = new;
	new = new->next;
	return (new);
}

void	build_lexer(t_lex *first, char *str, int len_str)
{
	int		i;
	t_lex	*new;
	char	buf[len_str + 1];
	char	read[2];

	i = 0;
	new = first;
	read[1] = '\0';
	ft_bzero(buf, len_str);
	while (str[i])
	{
		read[0] = str[i];
		if (new->token == OP && !g_quote)
		{
			if (is_op(str[i], buf) && cat_op(str[i], buf))
				ft_strcat(buf, read);
			else
			{
				new = put_in_new(new, buf, len_str);
				i--;
			}
		}
		else if (is_esc(str[i]) && !g_quote)
		{
			new->token = WORD;
			g_quote = str[i];
			ft_strcat(buf, read);
			if (g_quote == '\\')
			{
				i++;
				if (str[i])
				{
					read[0] = str[i];
					ft_strcat(buf, read);
					g_quote = 0;
				}
			}
		}
		else if (!g_quote && is_op(str[i], buf))
		{
			if (buf[0])
			{
				if (is_number(buf) && (str[i] == '>' || str[i] == '<'))
					new->token = IO_NUMBER;
				new = put_in_new(new, buf, len_str);
			}
			ft_strcat(buf, read);
			new->token = OP;
		}
		else if (!g_quote && (str[i] == '\n' || str[i] == ' '))
		{
			if (new->token != NONE)
				new = put_in_new(new, buf, len_str);
		}
		else if (new->token == WORD || new->token == QUOTE || str[i] == g_quote)
		{
			if (str[i] == g_quote)
				g_quote = 0;
			ft_strcat(buf, read);
		}
		else if (str[i] == '#')
			while (str[i] != '\n')
				i++;
		else
		{
			ft_bzero(buf, len_str);
			ft_strcat(buf, read);
			new->token = WORD;
		}
		i++;
	}
	if (new->token != NONE)
		new = put_in_new(new, buf, len_str);
	new->token = EOI;
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
