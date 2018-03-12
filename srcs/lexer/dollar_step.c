/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_step.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:49:11 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/12 17:07:50 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*dollar_step(t_lex *new, char *str, int *i, char buf[])
{
	int	j;

	j = *i + 1;
	concat_char(str, *i, buf);
	if (str[j] == '{')
	{
		while (str[j] && str[j] != '}')
		{
			concat_char(str, j, buf);
			j++;
		}
		if (!str[j])
		{
			new->token = QUOTE;
			g_quote = str[*i + 1];
		}
		else
			concat_char(str, j, buf);
		*i = (!str[j]) ? j - 1 : j;
	}
	if (new->token == NONE)
		new->token = WORD;
	return (new);
}
