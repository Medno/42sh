/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:30:39 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/07 09:57:05 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		print_history(t_hist **histo, char *str)
{
	t_hist	*tmp;

	(void)str;
	tmp = *histo;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		ft_printf("%d %s\n", tmp->nb, tmp->line);
		tmp = tmp->next;
	}
	return (0);
}
