/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:19:00 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/21 18:44:10 by pchadeni         ###   ########.fr       */
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

char		*dollar_exp(t_init *init, char *str, char ***tab, int *index)
{
	char	*res;
	int		replace;

	res = ft_strdup("");
	replace = 0;
	res = dollar_checkstr(init, str, res, &replace);
	if (replace && !init->dollar)
	{
		if (ft_strchr(res, ' ') && replace == 1)
			return (return_newtab(res, tab, index));
		ft_strdel(&str);
		return (res);
	}
	ft_strdel(&res);
	return (str);
}
