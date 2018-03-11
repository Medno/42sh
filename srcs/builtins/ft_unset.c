/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:57:14 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 14:40:39 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_alnum(char *str)
{
	int		j;
	
	j = 0;
	while (str[j])
	{
		if (!ft_isalnum(str[j]))
			return (0);
		j++;
	}
	return (1);
}

int		is_in_env(t_env *env, char *name)
{
	while (env && !ft_strequ(name, env->name))
		env = env->next;
	if (!env)
		return (0);
	return (1);
}

int		ft_unset(t_env **loc, t_env **env, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!check_alnum(arg[i]))
		{
			ft_printf_fd(STDERR_FILENO, "42sh: `%s': not a valid identifier\n",
					arg[i]);
			return (1);
		}
		if (is_in_env(*loc, arg[i]))
			ft_unsetenv(loc, arg[i]);
		else if (is_in_env(*env, arg[i]))
			ft_unsetenv(env, arg[i]);
		i++;
	}
	return (0);
}
