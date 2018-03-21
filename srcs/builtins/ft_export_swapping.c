/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_swapping.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:08:12 by hlely             #+#    #+#             */
/*   Updated: 2018/03/21 13:08:48 by hlely            ###   ########.fr       */
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
