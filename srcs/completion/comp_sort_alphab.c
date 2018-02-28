/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_cmd.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2017/02/20 18:20:51 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int		is_sorted(t_lcomp *list)
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

void	comp_sort_alphab(t_comp *comp)
{
	t_lcomp *tmp;
	char *tmp2;

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