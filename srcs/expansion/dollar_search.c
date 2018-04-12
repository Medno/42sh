/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:05:38 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/12 10:45:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*search_in_env(t_init *init, char buf[])
{
	char	*res;
	char	*in_env;

	if (ft_strequ("?", buf))
		res = ft_itoa(g_status);
	else
	{
		if (!(in_env = ft_getenv(&init->new_env, buf)))
			in_env = ft_getenv(&init->loc_env, buf);
		res = (buf[0] && in_env) ? ft_strdup(in_env) : NULL;
	}
	return (res);
}

static char	*search_dollar(t_init *init, char *str, int *i, int len)
{
	char	*res;
	char	buf[len];
	int		brace;

	ft_bzero(buf, len);
	(*i)++;
	brace = (str[*i] && str[*i] == '{') ? 1 : 0;
	*i = (brace) ? *i + 1 : *i;
	while (str[*i])
	{
		if (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '-' ||
				(str[*i] == '?' && !buf[0]))
			put_in_buffer(buf, str[*i]);
		else if (!ft_isalnum(str[*i]) && brace && str[*i] != '}')
			return (err_dollar(init, str));
		else
			break ;
		(*i)++;
	}
	res = search_in_env(init, buf);
	*i = (brace) ? *i + 1 : *i;
	return (res);
}

static char	*not_dollar(char *res, char *str, int i, int end)
{
	char	*tmp;

	tmp = ft_strsub(str, i, end - i);
	res = ft_strjoindel(res, tmp);
	ft_strdel(&tmp);
	return (res);
}

char		*dollar_modify_str(t_init *init, char *str, int *replace, int *i)
{
	char	*tmp;
	char	*res;
	int		end;
	int		len;

	res = ft_strdup("");
	end = get_unquoted_dollar(str, *i, replace);
	len = ft_strlen(str);
	if (*i < end)
		res = not_dollar(res, str, *i, end);
	*i = (*i == end && !str[*i + 1]) ? *i + 1 : end;
	if (str[*i] && str[*i + 1] && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'
			|| str[*i + 1] == '-' || str[*i + 1] == '{' || str[*i + 1] == '?'))
	{
		tmp = search_dollar(init, str, i, len + 1);
		*replace = (*replace == 2 || (tmp && !ft_strchr(tmp, ' '))) ? 2 : 1;
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
