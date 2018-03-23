/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 09:16:11 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

int			is_separ(char *str, int index)
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

void		start_at_separ(t_comp *comp)
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

void		from_list_to_comp(t_line *cur, t_comp *comp)
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

/*
**	On creer le t_comp
**	On remplit le t_comp en fonction de la list
**	On modifie le t_comp en fonction de la completion
**	Si on a trouvé une possibilité, on modifie la list et on l'affiche
**	En cas de solution unique, on rajoute '/' ou ' ' à la fin
*/

t_line		*completion(t_edit *edit)
{
	if ((*edit->current)->c == '0' && (*edit->current)->prev == NULL)
		return (*edit->current);
	from_list_to_comp(*edit->current, edit->comp);
	do_completion(edit->comp, edit);
	if (edit->comp->current)
	{
		*edit->current = print_completion(*edit->current, edit);
		if (edit->comp->list->next == NULL)
			reset_completion('0', edit->comp);
	}
	return (*edit->current);
}
