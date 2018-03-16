/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:08:45 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/15 17:36:30 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_env		*fill_env(t_env *env, char **arg)
{
	int		i;
	char	*name;
	char	*value;

	i = 2;
	while (arg[i] && ft_strchr(arg[i], '='))
	{
		name = ft_strsub(arg[i], 0, equ_index(arg[i], '='));
		value = ft_strchr(arg[i], '=') + 1;
		ft_setenv(&env, name, value);
		ft_strdel(&name);
		i++;
	}
	if (!arg[i])
	{
		ft_print_env(env);
		free_list(&env);
		return (NULL);
	}
	return (env);
}

int			ft_env_i(t_init *init, char **arg)
{
	t_env	*new;
	t_init	*initmp;

	new = NULL;
	new = fill_env(new, arg);
	if (new)
	{
		initmp = init;
		initmp->new_env = new;
		ft_putendl("here");
		initmp->ast->cmd->arg += 2;
		check_cmd(initmp->ast, initmp);
	}
	return (0);
}

int			ft_env_u(t_init *init, char **arg)
{
	t_env	*new;

	(void)init;
	new = NULL;
	new = fill_env(new, arg);
	return (0);
}

int			ft_env(t_init *init, char ***entry)
{
	char	**arg;

	arg = *entry;
	if (!arg[1])
		ft_print_env(init->new_env);
	else if (ft_strequ(arg[1], "-i"))
		return (ft_env_i(init, arg));
	else if (ft_strequ(arg[1], "-u"))
		return (ft_env_u(init, arg));
	return (0);
}
