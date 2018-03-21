/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:52:05 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/21 17:03:50 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"

void	expand_list(t_glpath **list)
{
	t_glpath	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (check_glob(tmp->str))
			write(1, "[!]\n", 4);
		tmp = tmp->next;
	}
}
