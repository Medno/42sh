/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:47:01 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/12 18:40:55 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_lex	*lex_copy_str(t_lex *new, char *str, int *i)
{
	int	j;

	j = 1;
	if (str[*i] == ';')
	{
		new->token = SEMICOLON;
		new->value = ft_strdup(";");
		return (new);
	}
	while (ft_isalnum(str[*i + j]))
		j++;
	new->token = STR;
	new->value = ft_strndup(&str[*i], j);
	*i += j;
	return (new);
}

t_lex	*lex_copy_int(t_lex *new, char *str, int *i)
{
	int	res;
	int	j;

	j = 0;
	res = 0;
	while (ft_isdigit(str[*i + j]))
	{
		res = (res * 10) + str[*i + j] - '0';
		j++;
	}
	if (str[*i] && ft_isalpha(str[*i + j]) && !isredir(str[*i + j]))
		return (lex_copy_str(new, str, i));
	new->token = INT;
	new->number = res;
	*i += j;
	return (new);
}

t_lex	*lex_copy_redir(t_lex *new, char *str, int *i)
{
	int	j;

	j = 0;
	new->token = REDIR;
	if (str[*i] == '|')
		new->value = ft_strdup("|");
	else
	{
		if (str[*i + 1] && (isredir(str[*i + 1] || str[*i + 1] == '&')))
			j = 1;
	}
	return (new);
}
