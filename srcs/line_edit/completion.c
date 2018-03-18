/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 14:03:21 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

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
}

void	ft_clean_screen_comp(t_comp *comp)
{
	if (ft_strlen(comp->str) > 0)
	 	ansi("LE", ft_strlen(comp->str), STDIN_FILENO);
	ansi("CL_END", 0, STDIN_FILENO);
}

/*
**	La liste en entree = "[prefix][completion]->cur<-[suffixe]"
**	On stock [suffix] dans str
**	On ecrit [completion]
**	On ecrit suffix
**	On replace le curseur a la fin de [completion]
*/

void	print_completion(t_line *cur, t_comp *comp, t_curs *curs)
{
	char	*str;
	t_line	*tmp;
	int		i;

	i = 0;
	ft_clean_screen_comp(comp);
	str = ft_strnew(parted_tline_len(cur));
	tmp = cur;
	while (tmp->next)
	{
		str[i] = tmp->c;
		if (tmp->c == '\n' && tmp->prev && tmp->index % curs->screen.ws_col == 1
			&& tmp->prev->c != '\n')
		{
			str[i] = '\n';
			str[++i] = '\n';
		}
		i++;
		tmp = tmp->next;
	}
	write(STDIN_FILENO, comp->current->cmd, ft_strlen(comp->current->cmd));	
	write(STDIN_FILENO, str, i);
	if (str && ft_strlen(str) > 0)
		ansi("LE", ft_strlen(str), STDIN_FILENO);
}

/*
**	On creer le t_comp
**	On remplit le t_comp en fonction de la list
**	On modifie le t_comp en fonction de la completion
**	Si on a trouvé une possibilité, on modifie la list en fonction du t_comp
*/

t_line	*completion(t_edit *edit)
{
	t_line *tmp;

	tmp = *edit->current;
	if (tmp->c == '0' && tmp->prev == NULL)
		return (*edit->current);
	from_list_to_comp(*edit->current, edit->comp);
	do_completion(edit->comp, edit->env);
	if (edit->comp->current)
	{
		*edit->current = from_comp_to_list(*edit->current, edit);
		print_completion(*edit->current, edit->comp, &edit->curseur);
	}
	return (*edit->current);
}
