/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:27:39 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 16:38:03 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	swapping_env(t_env **loc_env, t_env **env, char *arg)
{
	t_env	*tmp;

	tmp = *loc_env;
	while (tmp && !ft_strequ(arg, tmp->name))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	ft_setenv(env, arg, tmp->content);
	ft_unsetenv(loc_env, arg);
	return (1);
}

int			ft_export(t_env **loc_env, t_env **env, char **arg)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (!is_valid_identifier(arg[i], PRINT))
		{
			i++;
			continue ;
		}
		if (ft_strchr(arg[i], '='))
			ft_set_variable(env, arg[i]);
		else if (!swapping_env(loc_env, env, arg[i]))
		{
			i++;
			continue ;
		}
		i++;
	}
	return (0);
}
