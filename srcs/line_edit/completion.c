/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 11:02:14 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void	put_current_to_prev(t_comp *comp)
{
	t_lcomp *tmp;

	if (comp->current->prev)
		comp->current = comp->current->prev;
	else
	{
		tmp = comp->list;
		while (tmp->next)
			tmp = tmp->next;
		comp->current = tmp;
	}
}

t_line		*completion_inv(t_edit *edit)
{
	if (!edit->comp->list || !edit->comp->list->next)
		return (*edit->current);
	edit->comp->str = ft_strdup(edit->comp->current->cmd);
	put_current_to_prev(edit->comp);
	*edit->current = print_completion(*edit->current, edit);
	edit->comp->reset = 0;
	ft_strdel(&edit->comp->str);
	return (*edit->current);
}

t_line		*do_simple_comp(t_edit *edit)
{
	ft_strdel(&edit->comp->str);
	edit->comp->str = ft_strdup(edit->comp->current->cmd);
	if (edit->comp->current->next)
		edit->comp->current = edit->comp->current->next;
	else
		edit->comp->current = edit->comp->list;
	*edit->current = print_completion(*edit->current, edit);
	edit->comp->reset = 0;
	return (*edit->current);
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
	edit->comp->reset = 0;
	if (edit->comp->list)
		do_simple_comp(edit);
	else
	{
		from_list_to_comp(*edit->current, edit->comp);
		do_completion(edit->comp, edit);
		if (edit->comp->current)
		{
			*edit->current = print_completion(*edit->current, edit);
			if (edit->comp->list->next == NULL)
			{
				edit->comp->reset = 1;
				reset_completion(edit->comp);
			}
		}
	}
	ft_clean_comp(edit->comp);
	return (*edit->current);
}
