/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:01:42 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/19 17:24:30 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"

static t_glob	*bufferize_globing(char **str, char *init)
{
	t_glob	*buf;

	buf = NULL;
	(void)str;
	(void)init;
	return (buf);
}

static t_glob	*check_wildcards(char *tmp, char *init, int quote, int bsh)
{
	t_glob	*list;

	list = NULL;
	while (*tmp)
	{
		if ((*tmp == '\"' && !quote) || (*tmp == '\"' && quote == 1))
			quote ^= 1;
		else if ((*tmp == '\'' && !quote) || (*tmp == '\'' && quote == 2))
			quote ^= 2;
		else if (*tmp == '\\' && *(tmp + 1) && *(tmp + 1) == '*')
		{
			bsh = 1;
			tmp++;
		}
		else if (*tmp == '*' && !quote && !bsh)
			list = bufferize_globing(&tmp, init);
		if (bsh)
			bsh = 0;
		tmp++;
	}
	return (list);
}

char			*ft_glob(char *init)
{
	t_glob	*globing_list;
	char	*tmp;
	char	*new;
	int		quote;
	int		backslash;

	tmp = init;
	quote = 0;
	backslash = 0;
	new = NULL;
	if (!ft_strchr(init, '*'))
		return (NULL);
	if (!(globing_list = check_wildcards(tmp, init, quote, backslash)))
		return (NULL);
	//new = expand_glob(globing_list);
	return (new);
}
