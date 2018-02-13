/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:56:45 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/13 15:23:51 by pchadeni         ###   ########.fr       */
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

	tmp = first;
	while (tmp && tmp->token != NONE)
	{
		if (tmp->token != INT)
			ft_putendl(tmp->value);
		else if (tmp->token == INT)
		{
			ft_putnbr(tmp->number);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}

t_lex	*treat_char(t_lex *new, char *str, int *i)
{
	if (isredir(str[*i]))
		new = lex_copy_redir(new, str, i);
	else if (str[*i] == '\'' || str[*i] == '\"')
		new = lex_copy_quote(new, str, i, ft_strlen(&str[*i]));
	else if (ft_isdigit(str[*i]))
		new = lex_copy_int(new, str, i);
	else
		new = lex_copy_str(new, str, i);
	return (new);
}

void	build_lexer(t_lex **first, char *str)
{
	t_lex	*new;
	int		i;

	i = 0;
	*first = init_lexer();
	new = *first;
	while (str[i])
	{
		new = treat_char(new, str, &i);
		if (str[i] && str[i] == ' ')
			i++;
		if (str[i])
		{
			new->next = init_lexer();
			new->next->prev = new;
			new = new->next;
		}
	}
}

t_lex	*lexer(char *str)
{
	t_lex	*first;

	if (!str)
		return (NULL);
	build_lexer(&first, str);
	print_lex(first);
	del_lex(first);
	return (first);
}
