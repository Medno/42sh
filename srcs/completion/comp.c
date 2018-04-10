/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:49:44 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:49:50 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

t_lcomp	*lcomp_push_back(t_lcomp *list, t_lcomp *new)
{
	t_lcomp *tmp;

	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (list);
}

t_lcomp	*init_t_lcomp(void)
{
	t_lcomp *new;

	new = ft_memalloc(sizeof(t_comp));
	return (new);
}

t_comp	*init_t_comp(void)
{
	t_comp *new;

	new = ft_memalloc(sizeof(t_comp));
	return (new);
}
