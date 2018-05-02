/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:32:21 by hlely             #+#    #+#             */
/*   Updated: 2018/03/19 13:34:13 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**cpytab(char **dest, char **src)
{
	int		i;

	i = 0;
	dest = (char**)ft_memalloc(sizeof(char*) * (ft_tablen(src) + 1));
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

t_env	*cpyenv(t_env *env)
{
	t_env	*new;
	t_env	*one;
	t_env	*tmp;

	new = NULL;
	while (env)
	{
		one = (t_env*)ft_memalloc(sizeof(t_env));
		one->name = ft_strdup(env->name);
		one->content = ft_strdup(env->content);
		if (!new)
			new = one;
		else
		{
			tmp = new;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = one;
		}
		env = env->next;
	}
	return (new);
}

char	**shift_arg(char **arg)
{
	int		i;
	char	**newarg;

	i = inc_opt(arg);
	newarg = NULL;
	while (arg[i] && ft_strchr(arg[i], '='))
		i++;
	newarg = cpytab(newarg, arg + i);
	return (newarg);
}

void	clean_init(t_init *init)
{
	t_hist	*tmp;

	while (init->historic)
	{
		tmp = init->historic;
		ft_strdel(&init->historic->line);
		init->historic->prev = NULL;
		init->historic = init->historic->next;
		tmp->next = NULL;
		ft_memdel((void**)&tmp);
	}
	ft_strdel(&init->pwd);
	free_list(&init->new_env);
	free_list(&init->loc_env);
}
