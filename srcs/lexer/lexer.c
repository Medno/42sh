/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:56:45 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/15 13:45:32 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		isredir(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

void	print_lex(t_lex *first)
{
	t_lex	*tmp;
	int		i;

	tmp = first;
	i = 1;
	while (tmp && tmp->token != NONE)
	{
		ft_printf("Token n. : %d\n", i);
		if (tmp->token != INT)
			ft_putendl(tmp->value);
		else if (tmp->token == INT)
		{
			ft_putnbr(tmp->number);
			write(1, "\n", 1);
		}
		i++;
		tmp = tmp->next;
	}
}
/*
t_lex	*treat_char(t_lex *new, char *str, int *i)
{
	if (isredir(str[*i]))
		new = lex_copy_redir(new, str, i);
	else if (str[*i] == '#')
		while (str[*i])
			(*i)++;
	else if (str[*i] == '\'' || str[*i] == '\"' || str[*i] == '`')
		new = lex_copy_quote(new, str, i, ft_strlen(&str[*i]));
	else if (ft_isdigit(str[*i]))
		new = lex_copy_int(new, str, i);
	else
		new = lex_copy_str(new, str, i);
	return (new);
}
*/


int		is_op(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '-' || c == '(' || c == ')'
			|| c == ';' || c == '|')
		return (1);
	return (0);
}

int		is_esc(char c)
{
	if (c == '\\' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

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

void	build_lexer(t_lex **first, char *str, int len_str)
{
	t_lex	*new;
	int		i;
	int		quoted;
	char	buf[len_str];
	char	read[2];

	i = 0;
	*first = init_lexer();
	new = *first;
	quoted = 0;
	read[1] = '\0';
	ft_bzero(buf, len_str);
	while (str[i])
	{
		read[0] = str[i];
		if (new->token == OP && !quoted && is_op(str[i]))
		{
			if (cat_op(str[i], buf))
				ft_strcat(buf, read);
			else
			{
				new->value = ft_strdup(buf);
				ft_bzero(buf, len_str);
				new->next = init_lexer();
				new->next->prev = new;
				new = new->next;
				ft_strcat(buf, read);
			}
		}
		else if (is_esc(str[i]) && !quoted)
		{
			new->token = WORD;
			quoted = 1;
			ft_strcat(buf, read);
		}
		else if (!quoted && is_op(str[i]))
			new->token = OP;
		else if (!quoted && (str[i] == '\n' || str[i] == ' ') && new->token != NONE)
		{
			new->value = ft_strdup(buf);
			ft_bzero(buf, len_str);
			new->next = init_lexer();
			new->next->prev = new;
			new = new->next;
		}
		else if (new->token == WORD)
		{
			if (is_esc(str[i]))
				quoted = 0;
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
	if (new == *first)
		new->token = EOI;
	else
		new->value = ft_strdup(buf);
}

t_lex	*lexer(char *str)
{
	t_lex	*first;

	if (!str)
		return (NULL);
	build_lexer(&first, str, ft_strlen(str));
	print_lex(first);
	del_lex(first);
	return (first);
}
