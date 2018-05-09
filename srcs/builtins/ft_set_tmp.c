/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_tmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:08:31 by hlely             #+#    #+#             */
/*   Updated: 2018/05/09 10:51:01 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	cpy_tmp_env(t_init *init)
{
	t_env	*tmp1;

	tmp1 = init->new_env;
	while (tmp1)
	{
		ft_setenv(&init->env_tmp, tmp1->name, tmp1->content);
		tmp1 = tmp1->next;
	}
}

void		ft_set_tmp(t_init *init, t_ast *ast, char **arg)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	cpy_tmp_env(init);
	while (arg && arg[i] && ft_strchr(arg[i], '=') &&
			is_valid_identifier(NULL, arg[i], NOPRINT))
	{
		name = ft_strsub(arg[i], 0, equ_index(arg[i], '='));
		value = ft_strchr(arg[i], '=') + 1;
		ft_setenv(&init->env_tmp, name, value);
		ft_strdel(&name);
		i++;
	}
	if (arg && !arg[i] &&
			(!ast->parent || (ast->parent && ast->parent->value != PIPE)))
		ft_set_local(&init->loc_env, &init->new_env, arg);
}
