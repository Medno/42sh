/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:25:58 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/21 15:34:17 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int			only_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	**return_newtab(char *str, char **tab)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(str, ' ');
	ft_strdel(&tab[0]);
	while (tmp[i])
	{
		if (!only_space(tmp[i]))
			tab = ft_addstr_tab(tab, tmp[i]);
		i++;
	}
	return (tab);
}
