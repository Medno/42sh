/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:15:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 09:24:01 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_env	*new_env(char *name, char *content)
{
	t_env	*new_elem;

	if (!(new_elem = malloc(sizeof(t_env))))
	{
		ft_putendl_fd("pksh: setenv: Cannot allocate memory", 2);
		return (NULL);
	}
	new_elem->name = ft_strdup(name);
	new_elem->content = ft_strdup(content);
	new_elem->next = NULL;
	return (new_elem);
}

int				ft_setenv(t_env **env, char *name, char *content)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && tmp->next && ft_strcmp(name, tmp->name))
		tmp = tmp->next;
	if (!content)
	{
		ft_putendl_fd("setenv: invalid argument", STDERR_FILENO);
		return (1);
	}
	if (tmp && !ft_strcmp(name, tmp->name))
	{
		free(tmp->content);
		tmp->content = ft_strdup(content);
	}
	else
	{
		if (!*env)
			*env = new_env(name, content);
		else
			tmp->next = new_env(name, content);
	}
	return (0);
}
