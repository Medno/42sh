/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:16:09 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/11 11:58:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	incr_index_in_esc(char *str, int *i, char esc)
{
	while (str[*i] && str[*i] != esc && esc == '\'')
		(*i)++;
	if (esc == '\'')
		esc = 0;
	return (esc);
}

static void	check_escape(char *str, int *i, char *escape)
{
	if (*escape == '\\')
		*escape = 0;
	else if (*escape && str[*i] == *escape)
	{
		*escape = 0;
		(*i)++;
	}
	if (!*escape && str[*i] && is_quote_bslash(str[*i]))
	{
		*escape = str[*i];
		(*i)++;
	}
}

int			get_unquoted_dollar(char *str, int i, int *rep)
{
	static char	escape = 0;

	while (str[i])
	{
		check_escape(str, &i, &escape);
		if (escape == '\'')
			escape = incr_index_in_esc(str, &i, escape);
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
			i++;
		*rep = (str[i] && str[i] == '$' && escape == '\"') ? 2 : *rep;
		if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] != ' ' &&
				escape != '\\')
			return (i);
		if (str[i])
			i++;
	}
	return (i);
}
