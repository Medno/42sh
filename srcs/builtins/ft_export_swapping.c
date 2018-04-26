/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_swapping.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:08:12 by hlely             #+#    #+#             */
/*   Updated: 2018/04/26 17:58:34 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	swapping_env(t_init *init, char *arg, int where)
{
	t_env	*tmp;

	tmp = (where == TOENV) ? (init->loc_env) : (init->env_tmp);
	while (tmp && !ft_strequ(arg, tmp->name))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	if (where == TOLOC)
	{
		ft_setenv(&init->loc_env, arg, tmp->content);
		ft_unsetenv(&init->new_env, arg);
	}
	else
	{
		ft_setenv(&init->new_env, arg, tmp->content);
		ft_unsetenv(&init->loc_env, arg);
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
			swapping_env(init, arg[i], TOLOC);
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
			swapping_env(init, arg[i], TOENV);
		i++;
	}
	return (ret);
}
