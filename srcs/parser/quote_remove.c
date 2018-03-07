/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:28:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/07 18:56:40 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	put_in_buffer(char buf[], char c)
{
	int	len;

	len = ft_strlen(buf);
	buf[len] = c;
}

char	*treat_esc(char *res, char *str, int *i, int len)
{
	if (str[*i] == '\\')
		res = esc_backslash(res, str, i);
	else if (str[*i] == '\'')
		res = esc_simple_qu(res, str, i, len);
	else
		res = esc_double_qu(res, str, i, len);
	return (res);
}

char	*delete_esc(char *str, int len)
{
	char	*res;
	char	buf[len + 1];
	int		i;

	i = 0;
	ft_bzero(buf, len);
	res = ft_strdup("");
	while (str[i])
	{
		if (is_esc(str[i]))
		{
			if (buf[0])
			{
				res = ft_strjoindel(res, buf);
				ft_bzero(buf, len);
			}
			res = treat_esc(res, str, &i, len);
		}
		else
			put_in_buffer(buf, str[i]);
		i++;
	}
	res = (buf[0]) ? ft_strjoindel(res, buf) : res;
	ft_strdel(&str);
	return (res);
}

void	quote_remove(t_init *init)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = init->cmd;
	while (tmp->arg[i])
	{
		j = 0;
		while (tmp->arg[i][j] && !is_esc(tmp->arg[i][j]))
			j++;
		if (tmp->arg[i][j])
			tmp->arg[i] = delete_esc(tmp->arg[i], ft_strlen(tmp->arg[i]));
		ft_putendl(tmp->arg[i]);
		i++;
	}
}
