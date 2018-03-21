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
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static char	**split_intotab(char *str, char **tab, int *index)
{
	char	**res;
	char	**tmp;
	int		loop;

	tmp = ft_strsplit(str, ' ');
	res = addtab_index(tab, tmp, *index);
	loop = ft_tablen(tmp) - 1;
	while (loop)
	{
		(*index)++;
		loop--;
	}
	ft_freetab(tmp);
	ft_freetab(tab);
	return (res);
}

char		*return_newtab(char *res, char ***tab, int *index)
{
	*tab = split_intotab(res, *tab, index);
	ft_strdel(&res);
	return ((*tab)[*index]);
}
