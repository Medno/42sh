/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:47:01 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/13 15:04:50 by pchadeni         ###   ########.fr       */
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
	}
	else
	{
		while (ft_isalnum(str[*i + j]))
			j++;
		new->token = STR;
		new->value = ft_strndup(&str[*i], j);
	}
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

	j = 1;
	new->token = REDIR;
	if (str[*i] == '|')
		new->value = ft_strdup("|");
	else
	{
		if (str[*i + 1] && (isredir(str[*i + 1]) || str[*i + 1] == '&'))
			j++;
		new->value = ft_strndup(&str[*i], j);
	}
	*i += j;
	return (new);
}

char	treat_backslash(char c)
{
	if (c == 'a')
		return ('\a');
	if (c == 'b')
		return ('\b');
	if (c == 't')
		return ('\t');
	if (c == 'n')
		return ('\n');
	if (c == 'v')
		return ('\v');
	if (c == 'f')
		return ('\f');
	if (c == 'r')
		return ('\r');
	if (c == '\"')
		return ('\"');
	if (c == '\'')
		return ('\'');
	if (c == '\\')
		return ('\\');
	return (0);
}

t_lex	*lex_copy_quote(t_lex *new, char *str, int *i, int len)
{
	int		j;
	int		backslash;
	char	tmp[len];

	j = 1;
	ft_bzero(tmp, len);
	tmp[0] = str[*i];
	backslash = 0;
	while (str[*i + j + backslash] && str[*i + j + backslash] != tmp[0])
	{
		if (str[*i + j + backslash] == '\\' && (tmp[j] = treat_backslash(str[*i + j + 1 + backslash])))
			backslash++;
		else
			tmp[j] = str[*i + j + backslash];
		j++;
	}
	tmp[j] = str[*i + j + backslash];
	j++;
	tmp[j] = '\0';
	new->token = QUOTE;
	new->value = ft_strdup(tmp);
	*i += j + backslash;
	return (new);
}
