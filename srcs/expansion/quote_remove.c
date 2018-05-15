/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:28:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/09 12:09:14 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int			is_quote_bslash(char c)
{
	if (c == '\\' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

void		put_in_buffer(char buf[], char c)
{
	int	len;

	len = ft_strlen(buf);
	buf[len] = c;
}

static int	only_backslashandn(char *str, char buf[], int len, char **res)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
		{
			ft_bzero(buf, len + 1);
			*res = ft_strdup("");
			return (0);
		}
		else if (str[i + 1] && str[i + 1] == '\n')
			i += 2;
		else
		{
			ft_bzero(buf, len + 1);
			*res = ft_strdup("");
			return (0);
		}
	}
	ft_strdel(&str);
	return (1);
}

static char	*treat_esc(char *res, char *str, int *i)
{
	char	*to_join;
	int		len;

	to_join = NULL;
	len = ft_strlen(str);
	if (str[*i] == '\\')
		to_join = esc_backslash(str, i);
	else if (str[*i] == '\'')
		to_join = esc_simple_qu(str, i, len);
	else if (str[*i] == '\"')
		to_join = esc_double_qu(str, i, len);
	if (to_join)
		res = ft_strjoindel(res, to_join);
	ft_strdel(&to_join);
	return (res);
}

char		*delete_esc(char *str, int len)
{
	char	*res;
	char	buf[len + 1];
	int		i;

	i = 0;
	if (only_backslashandn(str, buf, len, &res))
		return (NULL);
	while (str && str[i])
	{
		if (is_quote_bslash(str[i]))
		{
			if (buf[0])
			{
				res = ft_strjoindel(res, buf);
				ft_bzero(buf, len);
			}
			res = treat_esc(res, str, &i);
		}
		else
			put_in_buffer(buf, str[i]);
		i++;
	}
	res = (buf[0]) ? ft_strjoindel(res, buf) : res;
	ft_strdel(&str);
	return (res);
}
