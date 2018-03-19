/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:57:14 by hlely             #+#    #+#             */
/*   Updated: 2018/03/19 15:41:53 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_unset(t_env **loc, t_env **env, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!is_valid_identifier("unset", arg[i], PRINT))
		{
			i++;
			continue ;
		}
		if (is_in_env(*loc, arg[i]))
			ft_unsetenv(loc, arg[i]);
		else if (is_in_env(*env, arg[i]))
			ft_unsetenv(env, arg[i]);
		i++;
	}
	return (0);
}
