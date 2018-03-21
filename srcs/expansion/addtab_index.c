/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtab_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:57:29 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/21 14:57:30 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**addtab_index(char **tab, char **add, int i)
{
	char	**res;
	int		index;

	if (i < 0 || i >= ft_tablen(tab))
		return (NULL);
	index = 0;
	res = NULL;
	while (tab[index])
	{
		if (index == i)
		{
			while (add[i - index])
			{
				res = ft_addstr_tab(res, add[i - index]);
				i++;
			}
			i = -1;
		}
		else
			res = ft_addstr_tab(res, tab[index]);
		index++;
	}
	return (res);
}
