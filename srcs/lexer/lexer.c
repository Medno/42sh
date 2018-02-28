/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:56:45 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/28 11:13:31 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		isredir(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

void	print_type(t_lex *tmp)
{
	ft_putstr("Type : ");
	if (tmp->token == NONE)
		ft_putendl("NONE");
	if (tmp->token == WORD)
		ft_putendl("WORD");
	if (tmp->token == OP)
		ft_putendl("OP");
	if (tmp->token == IO_NUMBER)
		ft_putendl("IO_NUMBER");
	if (tmp->token == EOI)
		ft_putendl("EOI");
	if (tmp->token == AND_IF)
		ft_putendl("AND_IF");
	if (tmp->token == OR_IF)
		ft_putendl("OR_IF");
	if (tmp->token == DSEMI)
		ft_putendl("DSEMI");
	if (tmp->token == DLESS)
		ft_putendl("DLESS");
	if (tmp->token == DGREAT)
		ft_putendl("DGREAT");
	if (tmp->token == LESSAND)
		ft_putendl("LESSAND");
	if (tmp->token == GREATAND)
		ft_putendl("GREATAND");
	if (tmp->token == LESSGREAT)
		ft_putendl("LESSGREAT");
	if (tmp->token == DLESSDASH)
		ft_putendl("DLESSDASH");
	if (tmp->token == CLOBBER)
		ft_putendl("CLOBBER");
}

void	print_lex(t_lex *first)
{
	t_lex	*tmp;
	int		i;

	tmp = first;
	i = 1;
	while (tmp)
	{
		ft_printf("Token n. : %d\n", i);
		print_type(tmp);
		ft_putendl(tmp->value);
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


int		is_op(char c, char buf[])
{
	if (c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
			|| c == ';' || c == '|')
		return (1);
	if (buf[0] && buf[1] && buf[0] == '<' && buf[1] == '<' && c == '-')
		return (1);
	return (0);
}

int		is_esc(char c)
{
	if (c == '\\' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		is_number(char buf[])
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (!ft_isdigit(buf[i]))
			return (0);
		i++;
	}
	if (buf[0])
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

t_lex	*categorize_token(t_lex *new)
{
	if (new->token == OP)
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
	}
	else if (!new->value)
	{
		new->token = EOI;
	}
	else if (ft_strequ("\n", new->value))
		new->token = NEWLINE;
	return (new);
}

void	build_lexer(t_lex **first, char *str, int len_str)
{
	t_lex	*new;
	int		i;
	char	buf[len_str + 1];
	char	read[2];

	i = 0;
	*first = init_lexer();
	new = *first;
	g_quote = 0;
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
				new->value = ft_strdup(buf);
				new = categorize_token(new);
				ft_bzero(buf, len_str);
				new->next = init_lexer();
				new->next->prev = new;
				new = new->next;
				i--;
			}
		}
		else if (is_esc(str[i]) && !g_quote)
		{
			new->token = WORD;
			g_quote = str[i];
			ft_strcat(buf, read);
		}
		else if (!g_quote && is_op(str[i], buf))
		{
			if (buf[0])
			{
				if (is_number(buf) && (str[i] == '>' || str[i] == '<'))
					new->token = IO_NUMBER;
				new->value = ft_strdup(buf);
				new = categorize_token(new);
				ft_bzero(buf, len_str);
				new->next = init_lexer();
				new->next->prev = new;
				new = new->next;
			}
			ft_strcat(buf, read);
			new->token = OP;
		}
		else if (!g_quote && (str[i] == '\n' || str[i] == ' '))
		{
			if (new->token != NONE)
			{
				new->value = ft_strdup(buf);
				new = categorize_token(new);
				ft_bzero(buf, len_str);
				new->next = init_lexer();
				new->next->prev = new;
				new = new->next;
			}
		}
		else if (new->token == WORD || str[i] == g_quote)
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
	if (new == *first && new->token == NONE)
		new->token = EOI;
	else
	{
		if (new->token != NONE)
		{
			new->value = ft_strdup(buf);
			new = categorize_token(new);
			new->next = init_lexer();
			new->next->prev = new;
			new = new->next;
		}
		new->token = EOI;
	}
}

t_lex	*lexer(char *str)
{
	t_lex	*first;

	g_quote = 0;
	if (!str)
		return (NULL);
	build_lexer(&first, str, ft_strlen(str));
	return (first);
}
