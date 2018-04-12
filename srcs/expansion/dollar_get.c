/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:16:09 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/12 10:49:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	not_escaped(char *str, int *i, int *rep, char *escape)
{
	if (str[*i] == '\"' && !*escape)
		*escape = '\"';
	else if (str[*i] == '\'' && !*escape)
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
	else
	{
		if (str[*i] && str[*i + 1] && str[*i] == '$' && str[*i + 1] == '$')
			(*i)++;
		*rep = (str[*i] && str[*i] == '$' && *escape == '\"') ? 2 : *rep;
		if (str[*i] && str[*i] == '$' && str[*i + 1] && str[*i + 1] != ' ')
			return (1);
	}
	if (str[*i])
		(*i)++;
	return (0);
}

int			get_unquoted_dollar(char *str, int i, int *rep)
{
	static char escape = 0;

	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (escape && str[i] == '\"')
		{
			escape = 0;
			i++;
		}
		else
		{
			if (not_escaped(str, &i, rep, &escape))
				return (i);
		}
	}
	return (i);
}
