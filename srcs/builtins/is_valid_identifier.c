/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:23:35 by hlely             #+#    #+#             */
/*   Updated: 2018/03/15 10:46:37 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_alnum(char *str)
{
	int		j;

	j = 0;
	while (str[j] && str[j] != '=')
	{
		if (!ft_isalnum(str[j]))
			return (0);
		j++;
	}
	return (1);
}

int			is_uid(char *arg)
{
	char	*name;
	int		free;

	free = 0;
	if (ft_strchr(arg, '='))
	{
		free = 1;
		name = ft_strsub(arg, 0, equ_index(arg, '='));
	}
	else
		name = arg;
	if (ft_strequ("UID", name))
	{
		free ? ft_strdel(&name) : 0;
		return (1);
	}
	free ? ft_strdel(&name) : 0;
	return (0);
}

int			is_valid_identifier(char *arg, int print)
{
	if (!(ft_isalpha(arg[0]) && arg[0] != '_') || !check_alnum(arg))
	{
		if (print)
			return (not_an_identifier(arg));
		return (0);
	}
	return (1);
}
