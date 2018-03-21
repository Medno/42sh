/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:01:42 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/21 14:47:57 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"

static void		free_glob(t_glpath **list)
{
	t_glpath	*tmp;
	t_glpath	*tmp2;

	while (*list)
	{
		tmp = *list;
		tmp2 = *list;
		while (tmp->next)
			tmp = tmp->next;
		if (tmp != tmp2)
		{
			while (tmp2->next != tmp)
				tmp2 = tmp2->next;
			tmp2->next = NULL;
		}
		ft_strdel(&tmp->str);
		ft_freetab(tmp->elem.pathv);
		if (!(*list)->next)
			ft_memdel((void **)&(*list));
		else
			ft_memdel((void **)&tmp);
	}
}

static char		*paste(t_glpath *list)
{
	char		*new;
	t_glpath	*tmp;

	new = NULL;
	tmp = list;
	while (tmp)
	{
		if (!new)
			new = ft_strdup(tmp->str);
		else
			new = ft_strjoindel(new, tmp->str);
		tmp = tmp->next;
	}
	return (new);
}

char			*ft_glob(char *init)
{
	t_glpath	*list;

	if (!init)
		return (init);
	list = parse_glob(init, ft_strlen(init));
	//>list with expans func
	ft_strdel(&init);
	init = paste(list);
	free_glob(&list);
	return (init);
}
