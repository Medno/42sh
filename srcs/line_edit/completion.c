/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 11:12:29 by kyazdani         ###   ########.fr       */
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
	if (*(edit->current)->c == '0' && *(edit->current)->prev == NULL)
		return (cur);
	from_list_to_comp(*(edit->current), edit->comp);
	do_completion(comp, edit->new_env);
	ft_printf("Ma string en sortie : [%s]\n", comp->cmd);
//	from_comp_to_list(cur, comp);
	
	(void)prompt;
	(void)curseur;

	return (cur);
}
