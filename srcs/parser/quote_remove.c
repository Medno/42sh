/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:28:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/06 17:55:31 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*clear_str(char *str, int i)
{
	(void)str;
	(void)i;
	return (NULL);
}

char	*new_str(char *str, int len_str)
{
	int		i;
	char	*res;
	char	buffer[len_str + 1];

	i = 0;
	ft_bzero(buffer, len_str);
	while (!is_esc(str[i]))
		i++;
	if (!str[i])
		return (str);
	res = ft_strndup(str, i);
	res = clear_str(str, i);
	ft_strdel(&str);
	return (res);
}

void	quote_remove(t_init *init)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = init->cmd;
	while (tmp->arg[i])
	{
		tmp->arg[i] = new_str(tmp->arg[i], ft_strlen(tmp->arg[i]));
		ft_putendl(tmp->arg[i]);
		i++;
	}
}
