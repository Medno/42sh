/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:15:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:53:45 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_env	*new_env(char *name, char *content)
{
	t_env	*new_elem;

	if (!(new_elem = malloc(sizeof(t_env))))
	{
		ft_putendl_fd("supershell: setenv: Cannot allocate memory", 2);
		return (NULL);
	}
	new_elem->name = ft_strdup(name);
	new_elem->content = ft_strdup(content);
	new_elem->next = NULL;
	return (new_elem);
}

void			ft_setenv(t_env **list, char *name, char *content)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp && tmp->next && ft_strcmp(name, tmp->name))
		tmp = tmp->next;
	if (!content)
		return ;
	if (tmp && !ft_strcmp(name, tmp->name))
	{
		free(tmp->content);
		tmp->content = ft_strdup(content);
	}
	else
	{
		if (!*list)
			*list = new_env(name, content);
		else
			tmp->next = new_env(name, content);
	}
}
