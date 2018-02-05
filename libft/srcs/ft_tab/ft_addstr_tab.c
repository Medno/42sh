/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:17:29 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/18 15:02:55 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_addstr_tab(char **array, char *str)
{
	char	**new_tab;
	int		i;

	if (!str && !array)
		return (NULL);
	if (!(new_tab = (char **)malloc(sizeof(char *) * (ft_tablen(array) + 2))))
		return (NULL);
	i = -1;
	if (array)
	{
		while (array[++i])
			new_tab[i] = ft_strdup(array[i]);
	}
	else
		i = 0;
	new_tab[i] = ft_strdup(str);
	new_tab[i + 1] = NULL;
	ft_freetab(array);
	return (new_tab);
}
