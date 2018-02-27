/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 13:16:01 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:53:52 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_unsetenv_2(t_env **list, t_env *tmp)
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
	free(tmp);
}

void		ft_unsetenv(t_env **list, char *name)
{
	t_env	*tmp;

	tmp = *list;
	if (!name)
	{
		ft_putendl_fd("unsetenv: usage: unsetenv [variable]", STDERR_FILENO);
		return ;
	}
	while (tmp && ft_strcmp(name, tmp->name))
		tmp = tmp->next;
	if (!tmp)
		ft_putendl_fd("unsetenv: no matches found", STDERR_FILENO);
	else
		ft_unsetenv_2(list, tmp);
}
