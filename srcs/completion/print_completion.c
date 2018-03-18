/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2018/03/02 11:22:58 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

/*
**	On va au debut de comp->str (la string a remplacée par completion)
**	On clean tout ce qu'il y a apres le curseur
*/

static void	ft_clean_screen_comp(t_comp *comp)
{
	if (ft_strlen(comp->str) > 0)
	 	ansi("LE", ft_strlen(comp->str), STDIN_FILENO);
	ansi("CL_END", 0, STDIN_FILENO);
}


/*
**	On créer ret de la taille nescessaire pour stocker la fin de la liste
**	On parcours la liste en partant du curseur pour remplir ret
**	On gère les sauts à la manière de Kiyan (voir avec lui si besoin ^^^)
*/

static char	*get_suffix(t_line *cur, t_curs *curs)
{
	char *ret;
	int		i;	
	t_line	*tmp;

	ret = ft_strnew(parted_tline_len(cur));
	tmp = cur;
	i = 0;
	while (tmp->next)
	{
		ret[i] = tmp->c;
		if (tmp->c == '\n' && tmp->prev && tmp->index % curs->screen.ws_col == 1
			&& tmp->prev->c != '\n')
		{
			ret[i] = '\n';
			ret[++i] = '\n';
		}
		i++;
		tmp = tmp->next;
	}
	return (ret);
}

/*
**	On part du debut de la liste, on note l'index de depart
**	On parcours la liste et on incrémente de 1 à chaque fois
*/

static void	reset_index_after_comp(t_line *cur)
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

/*
**	La liste en entree = "[prefix][completion]->cur<-[suffixe]"
**	On stock [suffix] dans str
**	On ecrit [completion]
**	On ecrit suffix
**	On replace le curseur a la fin de [completion]
*/

void		print_completion(t_line *cur, t_comp *comp, t_curs *curs)
{
	char	*str;

	ft_clean_screen_comp(comp);
	str = get_suffix(cur, curs);
	write(STDIN_FILENO, comp->current->cmd, ft_strlen(comp->current->cmd));	
	write(STDIN_FILENO, str, ft_strlen(str));
	if (str && ft_strlen(str) > 0)
		ansi("LE", ft_strlen(str), STDIN_FILENO);
	ft_strdel(&str);
	reset_index_after_comp(cur);
}
