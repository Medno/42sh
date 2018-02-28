/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:06:38 by hfouques          #+#    #+#             */
/*   Updated: 2017/01/25 21:45:59 by hfouques         ###   ########.fr       */
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
	return (list);
}

t_lcomp	*init_t_lcomp(void)
{
	t_lcomp *new;

	if ((new = ft_memalloc(sizeof(t_lcomp))))
		return (new);
	return (NULL);
}