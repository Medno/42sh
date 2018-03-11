/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:27:39 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 12:55:20 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_export(t_env **loc_env, t_env **env, char **arg)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (arg[i])
	{
		if (ft_strchr(arg[i], '='))
			ft_set_variable(env, arg[i]);
		else
		{
			tmp = *loc_env;
			while (tmp && !ft_strequ(arg[i], tmp->name))
				tmp = tmp->next;
			if (!tmp)
			{
				i++;
				continue ;
			}
			ft_setenv(env, arg[i], tmp->content);
			ft_unsetenv(loc_env, arg[i]);
		}
		i++;
	}
	return (0);
}
