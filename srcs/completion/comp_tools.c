/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:52:29 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:52:52 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

int		is_echaped(char *str, int index)
{
	char	*tmp;
	int		echap;

	if (index == 0)
		return (0);
	echap = 0;
	tmp = str;
	while (tmp && *tmp && tmp != str + index)
	{
		if (*tmp == '\\')
		{
			if (echap == 1)
				echap = 0;
			else
				echap = 1;
		}
		else
			echap = 0;
		tmp++;
	}
	return (echap);
}

int		is_delimiteur(char *str, int index)
{
	char c;

	c = str[index];
	if (c == ' ' || c == ':' || c == '>' || c == '=' || c == '<')
	{
		if (is_echaped(str, index))
			return (0);
		return (1);
	}
	return (0);
}

int		comp_is_first_word(t_comp *comp)
{
	int i;

	i = 0;
	while (comp->cmd[i] && comp->cmd[i] == ' ')
		i++;
	while (comp->cmd[i] && !is_delimiteur(comp->cmd, i))
		i++;
	if (i > comp->pos - 2)
		return (1);
	return (0);
}

int		comp_has_slash(char *str)
{
	if (ft_strchr(str, '/'))
		return (1);
	return (0);
}

char	*comp_go_to_last_slash(char *str)
{
	char *tmp;
	char *ret;

	tmp = str;
	ret = NULL;
	while (tmp && *tmp)
	{
		if (*tmp == '/')
			ret = tmp;
		tmp++;
	}
	return (ret);
}
