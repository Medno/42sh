/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 12:55:59 by hlely             #+#    #+#             */
/*   Updated: 2018/03/21 20:09:55 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_print_env(t_env *env, char c)
{
	while (env)
	{
		if (ft_strchr(env->content, ' ') || c == '"')
			ft_printf("%s=%c%s%c\n", env->name, c, env->content, c);
		else
			ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	return (0);
}
