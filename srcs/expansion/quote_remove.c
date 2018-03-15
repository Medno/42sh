/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:28:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/15 16:32:04 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int		is_quote_bslash(char c)
{
	if (c == '\\' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	put_in_buffer(char buf[], char c)
{
	int	len;

	len = ft_strlen(buf);
	buf[len] = c;
}

char	*treat_esc(t_init *init, char *res, char *str, int *i)
{
	char	*to_join;
	int		len;

	to_join = NULL;
	len = ft_strlen(str);
	if (!*i && str[*i] == '\\' && str[*i + 1] && str[*i + 1] == '\n' &&
			!str[*i + 2])
		ft_strdel(&res);
	else if (str[*i] == '\\')
		to_join = esc_backslash(str, i);
	else if (str[*i] == '\'')
		to_join = esc_simple_qu(str, i, len);
	else if (str[*i] == '\"')
		to_join = esc_double_qu(init, str, i, len);
	if (to_join)
		res = ft_strjoindel(res, to_join);
	ft_strdel(&to_join);
	return (res);
}

char	*delete_esc(t_init *init, char *str, int len)
{
	char	*res;
	char	buf[len + 1];
	int		i;

	i = 0;
	ft_bzero(buf, len + 1);
	res = ft_strdup("");
	while (str[i])
	{
		if (is_quote_bslash(str[i]))
		{
			if (buf[0])
			{
				res = ft_strjoindel(res, buf);
				ft_bzero(buf, len);
			}
			res = treat_esc(init, res, str, &i);
		}
		else
			put_in_buffer(buf, str[i]);
		i++;
	}
	res = (buf[0]) ? ft_strjoindel(res, buf) : res;
	ft_strdel(&str);
	return (res);
}
