/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:09:07 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/28 18:28:30 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

void	del_lex(t_lex *lex)
{
	t_lex	*tmp;

	while (lex)
	{
		tmp = lex->next;
		del_one_lex(lex);
		lex = tmp;
	}
}
