/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_list_to_comp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:51:27 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:51:28 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int		is_separ(char *str, int index)
{
	char c;

	c = str[index];
	if (c == ';' || c == '&' || c == '|' || c == '(' || c == '`')
	{
		if (is_echaped(str, index))
			return (0);
		return (1);
	}
	return (0);
}

static void		start_at_separ(t_comp *comp)
{
	int		index;
	char	*to_del;

	if (comp->pos == 1)
		return ;
	index = comp->pos - 2;
	while (index >= 0)
	{
		if (is_separ(comp->cmd, index))
			break ;
		index--;
	}
	if (index != -1)
	{
		if (comp->cmd[index + 1])
			index++;
		to_del = comp->cmd;
		comp->cmd = ft_strdup(comp->cmd + index);
		comp->pos -= (ft_strlen(to_del) - ft_strlen(comp->cmd));
		ft_strdel(&to_del);
	}
}

/*
**	On transforme la liste en string qu'on stock dans comp->cmd
**	On stock la position dans comp->pos
**	/!\ Le prompt incrémente l'index et empeche de s'en servir
*/

void			from_list_to_comp(t_line *cur, t_comp *comp)
{
	t_line *tmp;

	comp->cmd = line_to_str(cur);
	tmp = cur;
	comp->pos = 0;
	while (tmp->prev)
	{
		tmp = tmp->prev;
		comp->pos++;
	}
	comp->pos++;
	start_at_separ(comp);
}
