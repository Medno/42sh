/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:52:05 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/21 17:28:23 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"

void	expand_list(t_glpath **list)
{
	t_glpath	*tmp;
	int			ret;

	tmp = *list;
	while (tmp)
	{
		if ((ret = check_glob(tmp->str)))
		{
			if (ret == 1)
				;//interrogate and wildcard
			else if (ret == 2)
				;//brackets solid
			else if (ret == 3)
				;//brackets
		}
		tmp = tmp->next;
	}
}
