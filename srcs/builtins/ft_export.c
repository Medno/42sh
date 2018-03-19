/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:27:39 by hlely             #+#    #+#             */
/*   Updated: 2018/03/19 15:41:21 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	swapping_env(t_env **loc, t_env **env, char *arg, int where)
{
	t_env	*tmp;

	tmp = (where == TOENV) ? *loc : *env;
	while (tmp && !ft_strequ(arg, tmp->name))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	if (where == TOLOC)
	{
		ft_setenv(loc, arg, tmp->content);
		ft_unsetenv(env, arg);
	}
	else
	{
		ft_setenv(env, arg, tmp->content);
		ft_unsetenv(loc, arg);
	}
	return (1);
}

int			export_equal(t_init *init, char *arg, int whereto)
{
	char	*name;
	char	*value;

	name = ft_strsub(arg, 0, equ_index(arg, '='));
	value = ft_strchr(arg, '=') + 1;
	if (whereto == TOENV)
	{
		ft_setenv(&init->new_env, name, value);
		if (is_in_env(init->loc_env, name))
			ft_unsetenv(&init->loc_env, name);
	}
	else
	{
		ft_setenv(&init->loc_env, name, value);
		if (is_in_env(init->new_env, name))
			ft_unsetenv(&init->new_env, name);
	}
	ft_strdel(&name);
	return (0);
}

int			switch_env_to_loc(t_init *init, char **arg)
{
	int		i;
	int		ret;

	i = 2;
	ret = 0;
	while (arg[i])
	{
		if (!is_valid_identifier("export", arg[i], PRINT))
		{
			i++;
			ret = 1;
			continue ;
		}
		if (ft_strchr(arg[i], '='))
			ret = export_equal(init, arg[i], TOLOC);
		else
			swapping_env(&init->loc_env, &init->new_env, arg[i], TOLOC);
		i++;
	}
	return (ret);
}

int			switch_loc_to_env(t_init *init, char **arg)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (arg[i])
	{
		if (!is_valid_identifier("export", arg[i], PRINT))
		{
			i++;
			ret = 1;
			continue ;
		}
		if (ft_strchr(arg[i], '='))
			ret = export_equal(init, arg[i], TOENV);
		else
			swapping_env(&init->loc_env, &init->new_env, arg[i], TOENV);
		i++;
	}
	return (ret);
}

int			ft_export(t_init *init, char ***entry)
{
	char	**arg;

	arg = *entry;
	if (!arg[1] || ft_strequ(arg[1], "-p"))
	{
		ft_print_env(init->new_env);
		return (0);
	}
	if (arg[1] && ft_strequ(arg[1], "-n"))
		return (switch_env_to_loc(init, arg));
	else if (arg[1] && arg[1][0] == '-')
		return (export_usage(arg[1]));
	else
		return (switch_loc_to_env(init, arg));
	return (0);
}
