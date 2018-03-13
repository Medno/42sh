/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:57:14 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 16:38:32 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_unset(t_init *init, char ***entry)
{
	int		i;
	char	**arg;

	i = 0;
	arg = *entry;
	while (arg[i])
	{
		if (!is_valid_identifier(arg[i], PRINT))
		{
			i++;
			continue ;
		}
		if (is_in_env(*(&init->loc_env), arg[i]))
			ft_unsetenv(&init->loc_env, arg[i]);
		else if (is_in_env(*(&init->new_env), arg[i]))
			ft_unsetenv(&init->new_env, arg[i]);
		i++;
	}
	return (0);
}
