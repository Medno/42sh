/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2017/02/20 18:20:51 by hfouques         ###   ########.fr       */
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