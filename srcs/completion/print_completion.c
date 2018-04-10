/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:09:06 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 10:09:09 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

/*
**	On del le char à gauche du curseur pour la longueur de la string a remplacer
*/

static t_line	*ft_clean_screen_comp(t_comp *comp, t_curs *curs, t_line *cur)
{
	int i;

	i = 0;
	while (i < ft_strlen(comp->str))
	{
		cur = line_delone(cur, curs);
		i++;
	}
	return (cur);
}

static int		comp_is_directory(t_comp *comp)
{
	struct stat	sb;
	int			ret;
	char		*file_path;

	file_path = ft_strjoin(comp->dir, comp->current->cmd);
	if (!file_path || stat(file_path, &sb) != 0)
		ret = 0;
	else
	{
		if (S_ISDIR(sb.st_mode))
			ret = 1;
		else
			ret = 0;
	}
	ft_strdel(&file_path);
	return (ret);
}

/*
**	On part du debut de la liste, on note l'index de depart
**	On parcours la liste et on incrémente de 1 à chaque fois
*/

static void		reset_index_after_comp(t_line *cur)
{
	t_line	*tmp;
	int		index;

	tmp = cur;
	while (tmp->prev)
		tmp = tmp->prev;
	index = tmp->index;
	while (tmp)
	{
		tmp->index = index;
		tmp = tmp->next;
		index++;
	}
}

static t_line	*comp_validate_choice(t_line *cur, t_edit *edit)
{
	if (edit->comp->list->next)
		return (cur);
	if (comp_is_directory(edit->comp))
		cur = push_new(cur, '/', &edit->curseur);
	else if (!ft_isalnum(cur->c))
		cur = push_new(cur, ' ', &edit->curseur);
	return (cur);
}

/*
**	La liste en entree = "[prefix][completion]->cur<-[suffixe]"
**	On clean l'ancienne valeur de [completion]
**	On ré-ecrit [completion]
**	On ecrit suffix
**	On remet les bonnes valeurs de index dans la liste
*/

t_line			*print_completion(t_line *cur, t_edit *edit)
{
	char *tmp;

	cur = ft_clean_screen_comp(edit->comp, &edit->curseur, cur);
	tmp = edit->comp->current->cmd;
	while (tmp && *tmp)
	{
		cur = push_new(cur, *tmp, &edit->curseur);
		tmp++;
	}
	cur = comp_validate_choice(cur, edit);
	reset_index_after_comp(cur);
	return (cur);
}
