/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:09:07 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/28 11:13:27 by kyazdani         ###   ########.fr       */
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
	tmp->number = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	del_lex(t_lex *lex)
{
	t_lex	*tmp;

	while (lex)
	{
		tmp = lex->next;
		lex->token = NONE;
		ft_strdel(&(lex->value));
		lex->number = 0;
		lex->next = NULL;
		lex->prev = NULL;
		free(lex);
		lex = tmp;
	}
}
