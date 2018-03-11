/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_local.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:30:23 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 12:48:41 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		clean_arg(char ***arg)
{
	int		i;
	int		j;
	char	**new_arg;

	i = 0;
	j = 0;
	while ((*arg)[j] && ft_strchr((*arg)[j], '='))
		j++;
	new_arg = (char**)ft_memalloc(sizeof(char**) * (ft_tablen((*arg + j)) + 1));
	while ((*arg)[j])
	{
		new_arg[i] = ft_strdup((*arg)[j]);
		j++;
		i++;
	}
	new_arg[i] = NULL;
	ft_freetab(*arg);
	*arg = new_arg;
	return (1);
}

int		check_local(char ***arg)
{
	int		i;

	i = 0;
	while ((*arg)[i])
	{
		if (!ft_strchr((*arg)[i], '='))
		{
			clean_arg(arg);
			return (0);
		}
		i++;
	}
	return (1);
}

int		equ_index(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_set_variable(t_env **loc_env, char *arg)
{
	char	*name;
	char	*value;

	name = ft_strsub(arg, 0, equ_index(arg, '='));
	value = ft_strchr(arg, '=') + 1;
	ft_setenv(loc_env, name, value);
	ft_strdel(&name);
}

int		ft_set_local(t_env **loc, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		ft_set_variable(loc, arg[i]);
		i++;
	}
	return (0);
}
