/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:06:38 by hfouques          #+#    #+#             */
/*   Updated: 2018/03/18 11:14:11 by kyazdani         ###   ########.fr       */
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
