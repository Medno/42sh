/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_swapping.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:08:12 by hlely             #+#    #+#             */
/*   Updated: 2018/05/02 12:17:46 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	swapping_env(t_init *init, char *arg, int where)
{
	t_env	*tmp;

	tmp = ft_getenv(&init->env_tmp, arg) ? init->env_tmp : init->loc_env;
	while (tmp && !ft_strequ(arg, tmp->name))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	if (where == TOLOC)
	{
		ft_setenv(&init->loc_env, arg, tmp->content);
		ft_getenv(&init->new_env, arg) ? ft_unsetenv(&init->new_env, arg) : 0;
	}
	else
	{
		ft_setenv(&init->new_env, arg, tmp->content);
		ft_getenv(&init->loc_env, arg) ? ft_unsetenv(&init->loc_env, arg) : 0;
	}
	return (1);
}

int			switch_env_to_loc(t_init *init, char **arg)
{
	int		i;
	int		ret;

	i = 0;
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
			swapping_env(init, arg[i], TOLOC);
		i++;
	}
	return (ret);
}

int			switch_loc_to_env(t_init *init, char **arg)
{
	int		i;
	int		ret;

	i = 0;
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
			swapping_env(init, arg[i], TOENV);
		i++;
	}
	return (ret);
}
