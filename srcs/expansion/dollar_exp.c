/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:19:00 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/11 19:03:07 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*dollar_checkstr(t_init *init, char *str, char *res, int *replace)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = dollar_modify_str(init, str, replace, &i);
		res = ft_strjoindel(res, tmp);
		ft_strdel(&tmp);
	}
	return (res);
}

char		**exp_dollar(t_init *init, char **tab)
{
	char	*res;
	int		replace;

	res = ft_strdup("");
	replace = 0;
	res = dollar_checkstr(init, tab[0], res, &replace);
	if (replace && !init->dollar)
	{
		if (replace == 1)
			return (return_newtab(res, tab));
		ft_strdel(&tab[0]);
		tab = ft_addstr_tab(tab, res);
		ft_strdel(&res);
		return (tab);
	}
	ft_strdel(&res);
	return (tab);
}
