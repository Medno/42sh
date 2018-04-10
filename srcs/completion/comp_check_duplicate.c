/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_check_duplicate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:50:25 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:50:26 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void	rem_duplicate(t_lcomp *elm)
{
	t_lcomp *tmp;

	tmp = elm->next;
	elm->next = elm->next->next;
	ft_clean_lcomp(tmp);
}

void		comp_check_duplicate(t_comp *comp)
{
	t_lcomp *tmp;

	tmp = comp->list;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->cmd, tmp->next->cmd) == 0)
			rem_duplicate(tmp);
		tmp = tmp->next;
	}
}
