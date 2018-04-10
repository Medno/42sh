/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_sort_alphab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:51:40 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:51:41 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int	is_sorted(t_lcomp *list)
{
	t_lcomp *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->cmd, tmp->next->cmd) > 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void		comp_sort_alphab(t_comp *comp)
{
	t_lcomp *tmp;
	char	*tmp2;

	tmp = comp->list;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->cmd, tmp->next->cmd) > 0)
		{
			tmp2 = tmp->next->cmd;
			tmp->next->cmd = tmp->cmd;
			tmp->cmd = tmp2;
		}
		tmp = tmp->next;
	}
	if (is_sorted(comp->list) == 0)
		comp_sort_alphab(comp);
	return ;
}
