/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 13:16:01 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/05 15:40:57 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_unsetenv_2(t_env **list, t_env *tmp)
{
	t_env	*tmp2;

	tmp2 = *list;
	while (tmp2 != tmp && tmp2->next != tmp)
		tmp2 = tmp2->next;
	ft_strdel(&tmp->name);
	ft_strdel(&tmp->content);
	if (tmp == *list)
		*list = tmp->next;
	else
		tmp2->next = tmp->next;
	tmp->next = NULL;
	ft_memdel((void **)&tmp);
	return (0);
}

int			ft_unsetenv(t_env **list, char *name)
{
	t_env	*tmp;

	tmp = *list;
	if (!name)
	{
		ft_putendl_fd("unsetenv: usage: unsetenv [variable]", STDERR_FILENO);
		return (1);
	}
	while (tmp && ft_strcmp(name, tmp->name))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_putendl_fd("unsetenv: no matches found", STDERR_FILENO);
		return (1);
	}
	return (ft_unsetenv_2(list, tmp));
}
