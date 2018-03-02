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

int		reset_completion(char c, t_comp *comp)
{
	if (c != '\t')
	{
		comp->current = NULL;
		if (comp->list)
		{
			ft_clean_lcomp_list(comp->list);
			comp->list = NULL;
		}
	}
	ft_strdel(&(comp->dir));
	ft_strdel(&(comp->str));
	ft_strdel(&(comp->cmd));
	return (1);	
}

void	ft_clean_lcomp(t_lcomp *elm)
{
	if (elm)
	{
		ft_strdel(&(elm->cmd));
		free(elm);
	}
}

void	ft_clean_lcomp_list(t_lcomp *list)
{
	t_lcomp *tmp;

	tmp = list;
	while (tmp)
	{
		list = list->next;
		ft_strdel(&(tmp->cmd));
		free(tmp);
		tmp = list;
	}
}