/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:19:00 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/14 18:33:05 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		get_unquoted_dollar(char *str, int i)
{
	char	escape;

	escape = 0;
	while (str[i])
	{
		if (escape && str[i] == escape)
			escape = 0;
		else if (!escape && is_quote_bslash(str[i]))
		{
			escape = str[i];
			i++;
		}
		if (escape == '\'' || escape == '\\' || (str[i] && str[i] == '\\'))
		{
			i = (escape == '\\' || (str[i] && str[i] == '\\')) ? i + 1 : i;
			while (str[i] && str[i] != escape && escape != '\\')
				i++;
			escape = (escape != '\"') ? 0 : escape;
		}
		if (str[i] && str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*search_dollar(t_init *init, char *str, int i, int len)
{
	char	*res;
	char	buf[len];
	int		brace;

	ft_bzero(buf, len);
	res = ft_strndup(str, i);
	i++;
	brace = (str[i] && str[i] == '{') ? 1 : 0;
	while (str[i] && (ft_isalnum(str[i]) || (str[i] == '}' && brace)))
	{
		put_in_buffer(buf, str[i]);
		i++;
	}
	(void)init;
	if (buf[0])
	{

		ft_strjoindel(res, buf);
	}
	return (res);
}

char	*dollar_exp(t_init *init, char *str, int len)
{
	char	*res;
	int		i;

	i = 0;
	i = get_unquoted_dollar(str, i);
	if (str[i + 1] && ft_isalnum(str[i + 1]))
	{
		res = search_dollar(init, str, i, len + 1);
		ft_strdel(&str);
		return (res);
	}
	return (str);
}
