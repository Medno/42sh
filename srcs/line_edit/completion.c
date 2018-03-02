/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 09:52:41 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void	from_list_to_comp(t_line *cur, t_comp *comp)
{
	comp->cmd = line_to_str(cur);
	comp->pos = cur->index + 1;
}

/*
**	On creer le t_comp
**	On remplit le t_comp en fonction de la list
**	On modifie le t_comp en fonction de la completion
**	On modifie la list en fonction du t_comp
*/

t_line	*completion(t_edit *edit)
{
	t_line *tmp;

	tmp = *edit->current;
	if (tmp->c == '0' && tmp->prev == NULL)
		return (*edit->current);
	from_list_to_comp(*edit->current, edit->comp);
	do_completion(edit->comp, edit->env);
	ft_printf("Ma string en sortie : [%s]\n", edit->comp->cmd);
//	from_comp_to_list(cur, comp);
	return (*(edit->current));
}
