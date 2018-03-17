/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:19:00 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/16 16:12:31 by pchadeni         ###   ########.fr       */
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
		else if (!escape && is_quote_bslash(str[i]) && (escape = str[i]))
			i++;
		if (escape == '\'' || escape == '\\' || (str[i] && str[i] == '\\'))
		{
			i = (escape == '\\' || (str[i] && str[i] == '\\')) ? i + 1 : i;
			while (str[i] && str[i] != escape && escape != '\\')
				i++;
			escape = (escape != '\"') ? 0 : escape;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
			i++;
		if (str[i] && str[i] == '$')
			return (i);
		if (str[i])
			i++;
	}
	return (i);
}

char	*search_dollar(t_init *init, char *str, int *i, int len)
{
	char	*res;
	char	*in_env;
	char	buf[len];
	int		brace;

	res = NULL;
	ft_bzero(buf, len);
	(*i)++;
	brace = (str[*i] && str[*i] == '{') ? 1 : 0;
	*i = (brace) ? *i + 1 : *i;
	while (str[*i])
	{
		if (ft_isalnum(str[*i]))
			put_in_buffer(buf, str[*i]);
		else if (!ft_isalnum(str[*i]) && brace && str[*i] != '}')
			return (err_dollar(init, str));
		else
			break ;
		(*i)++;
	}
	if (buf[0] && (in_env = ft_getenv(&init->new_env, buf)))
		res = ft_strdup(in_env);
	*i = (brace) ? *i + 1 : *i;
	return (res);
}

char	*not_dollar(char *res, char *str, int i, int end)
{
	char	*tmp;

	tmp = ft_strsub(str, i, end - i);
	res = ft_strjoindel(res, tmp);
	ft_strdel(&tmp);
	return (res);
}

char	*exp_expr(t_init *init, char *str, int *replace, int *i)
{
	char	*tmp;
	char	*res;
	int		end;
	int		len;

	res = ft_strdup("");
	end = get_unquoted_dollar(str, *i);
	len = ft_strlen(str);
	if (*i < end)
		res = not_dollar(res, str, *i, end);
	*i = (*i == end && !str[*i + 1]) ? *i + 1 : end;
	if (str[*i] && str[*i + 1] && (ft_isalnum(str[*i + 1]) ||
				str[*i + 1] == '{'))
	{
		tmp = search_dollar(init, str, i, len + 1);
		*replace = 1;
		res = ft_strjoindel(res, tmp);
		ft_strdel(&tmp);
	}
	else if (str[*i] == '$' && !ft_isalnum(str[*i + 1]))
	{
		(*i)++;
		*replace = 0;
	}
	return (res);
}

char	*dollar_exp(t_init *init, char *str)
{
	char	*res;
	char	*tmp;
	int		replace;
	int		i;

	i = 0;
	res = ft_strdup("");
	replace = 0;
	while (str[i])
	{
		tmp = exp_expr(init, str, &replace, &i);
		res = ft_strjoindel(res, tmp);
		ft_strdel(&tmp);
	}
	if (replace && !init->dollar)
	{
		ft_strdel(&str);
		return (res);
	}
	ft_strdel(&res);
	return (str);
}