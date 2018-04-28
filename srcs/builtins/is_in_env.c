/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:19:00 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 15:19:25 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_in_env(t_env *env, char *name)
{
	while (env && !ft_strequ(name, env->name))
		env = env->next;
	if (!env)
		return (0);
	return (1);
}

char	*ft_getenvloc(t_init *init, char *elem)
{
	char *ret;

	ret = ft_getenv(&init->env_tmp, elem);
	if (!ret)
		ret = ft_getenv(&init->loc_env, elem);
	return (ret);
}
