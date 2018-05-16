/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:09:07 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/16 12:20:28 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*init_lexer(void)
{
	t_lex	*tmp;

	if (!(tmp = (t_lex *)malloc(sizeof(t_lex))))
		return (NULL);
	tmp->token = NONE;
	tmp->value = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	del_one_lex(t_lex *lex)
{
	lex->token = NONE;
	ft_strdel(&(lex->value));
	lex->next = NULL;
	lex->prev = NULL;
	free(lex);
	lex = NULL;
}

void	del_lex(t_lex **lex)
{
	t_lex	*tmp;

	while (*lex)
	{
		tmp = (*lex)->next;
		del_one_lex(*lex);
		*lex = tmp;
	}
}

t_lex	*get_lex(t_lex *first, t_token token, char *value)
{
	t_lex	*tmp;

	tmp = first;
	while (tmp && tmp->token != EOI)
	{
		if (value && ft_strequ(value, tmp->value))
			return (tmp);
		if (!value && token != NONE)
			if (token == tmp->token)
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_lex	*get_doublelex(t_lex *first, t_token token1,
		t_token token2, char *value)
{
	t_lex	*tmp;

	tmp = first;
	while (tmp && tmp->token != EOI)
	{
		if (value && ft_strequ(value, tmp->value))
			return (tmp);
		if (!value && token1 != NONE && token2 != NONE)
			if (token1 == tmp->token || token2 == tmp->token)
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
