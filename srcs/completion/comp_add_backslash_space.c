/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_add_backslash_space.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:50:11 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:50:13 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int		is_space_or_dollar(char c)
{
	if (c == ' ' || c == '$')
		return (1);
	return (0);
}

static int		nbr_of_space(char *str)
{
	int ret;
	int i;

	i = 0;
	ret = 0;
	while (str && str[i])
	{
		if (is_space_or_dollar(str[i]) && is_echaped(str, i) == 0)
			ret++;
		i++;
	}
	return (ret);
}

static void		add_backslash_for_space(t_lcomp *elem)
{
	int		n;
	char	*new;
	int		i;
	char	*tmp;

	n = nbr_of_space(elem->cmd);
	new = ft_strnew(ft_strlen(elem->cmd) + n);
	i = 0;
	tmp = new;
	while (i < ft_strlen(elem->cmd))
	{
		if (is_space_or_dollar(elem->cmd[i]) && is_echaped(elem->cmd, i) == 0)
		{
			*tmp = '\\';
			tmp++;
			*tmp = elem->cmd[i];
		}
		else
			*tmp = elem->cmd[i];
		tmp++;
		i++;
	}
	tmp = elem->cmd;
	elem->cmd = new;
	ft_strdel(&tmp);
}

void			comp_add_backslash_space(t_comp *comp)
{
	t_lcomp *tmp;

	tmp = comp->list;
	while (tmp)
	{
		if (ft_strchr(tmp->cmd, ' ') || ft_strchr(tmp->cmd, '$'))
		{
			add_backslash_for_space(tmp);
		}
		tmp = tmp->next;
	}
}
