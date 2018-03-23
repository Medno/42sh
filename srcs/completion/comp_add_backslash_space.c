/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_cmd.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2017/02/20 18:20:51 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"


static int		nbr_of_space(char *str)
{
	int ret;
	int i;

	i = 0;
	ret = 0;
	while (str && str[i])
	{
		if (str[i] == ' ' && is_echaped(str, i) == 0)
			ret++;
		i++;
	}
	return (ret);
}

static void		add_backslash_for_space(t_lcomp *elem)
{
	int		n;
	char	*new;
	int i;
	char	*tmp;

	n = nbr_of_space(elem->cmd);
	new = ft_strnew(ft_strlen(elem->cmd) + n);
	i = 0;
	tmp = new;
	while (i < ft_strlen(elem->cmd))
	{
		if (elem->cmd[i] == ' ' && is_echaped(elem->cmd, i) == 0)
		{
			
			*tmp = '\\';
			tmp++;
			*tmp = ' ';
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

void		comp_add_backslash_space(t_comp *comp)
{
	t_lcomp *tmp;

	tmp = comp->list;
	while (tmp && tmp->next)
	{
		if (ft_strchr(tmp->cmd, ' '))
		{
			add_backslash_for_space(tmp);
		}
		tmp = tmp->next;
	}
}