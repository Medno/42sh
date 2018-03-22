/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:07:48 by hlely             #+#    #+#             */
/*   Updated: 2018/03/22 10:42:06 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	**alloc_new_arg(char **arg)
{
	int		i;
	int		j;
	char	**new_arg;

	i = 0;
	j = 0;
	while (arg[j])
	{
		if (!only_space(arg[j]))
			i++;
		j++;
	}
	new_arg = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	return (new_arg);
}

static int	clean_arg(char ***arg)
{
	int		i;
	int		j;
	char	**new_arg;

	new_arg = alloc_new_arg(*arg);
	i = 0;
	j = 0;
	while ((*arg)[j])
	{
		if (!only_space((*arg)[j]))
		{
			new_arg[i] = ft_strtrim((*arg)[j]);
			i++;
		}
		j++;
	}
	new_arg[i] = NULL;
	ft_freetab(*arg);
	*arg = new_arg;
	return (1);
}

int			delete_space(t_ast *ast)
{
	if (ast && ast->cmd && ast->cmd->arg)
		return (clean_arg(&ast->cmd->arg));
	return (1);
}
