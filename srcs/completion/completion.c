/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:53:02 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:53:03 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

/*
**	Cas "./comp[]" ou "/Dossier/comp[]", on analyse les dossiers et executables
**	Cas "comp[] args", on analyse les executables du PATH
**	Cas "command dossier/comp[]" on analyse les dossiers et fichiers
**	On vérifie l'ordre alphabetique, on add les builtins et on vire les doublons
**	Comp->current prend la premiere valeur de la liste créee
*/

void	do_new_completion(t_comp *comp, t_edit *edit)
{
	if (comp->str && *comp->str == '$')
		comp_get_pot_local(comp, edit);
	else if (comp_is_first_word(comp) == 1)
	{
		if (comp->dir)
			comp_get_pot_dir_exec(comp);
		else
			comp_get_pot_cmd(comp, edit);
	}
	else
		comp_get_pot_dir(comp);
	comp_sort_alphab(comp);
	if (*comp->str != '$')
		comp_add_backslash_space(comp);
	comp_check_duplicate(comp);
	comp->current = comp->list;
}

/*
**	On avance current d'une node
**	Si current est la derniere node, on le place en tête de liste
*/

void	put_current_to_next(t_comp *comp)
{
	if (comp->current->next)
		comp->current = comp->current->next;
	else
		comp->current = comp->list;
}

/*
**	On decoupe cmd en "[prefix][comp a modifier][][suffix]"
**	On modifier en "[prefix][premier choix de la liste][suffix]"
**	On replace la postion du curseur en fonction de la completion
*/

void	comp_modify_cmd(t_comp *comp)
{
	char *prefix;
	char *suffix;

	prefix = ft_strsub(comp->cmd, 0, comp->pos - 1 - ft_strlen(comp->str));
	suffix = ft_strsub(comp->cmd, comp->pos - 1,
		ft_strlen(comp->cmd) - comp->pos + 1);
	comp->pos -= ft_strlen(comp->str);
	comp->pos += ft_strlen(comp->current->cmd);
	if (comp->cmd)
		ft_strdel(&(comp->cmd));
	comp->cmd = ft_strjoin_infinite(3, prefix, comp->current->cmd, suffix);
	ft_strdel(&prefix);
	ft_strdel(&suffix);
}

/*
**	On recuperer la string à completer
**	On isole le potentiel directory de la string (Cas : "../../Dossi[]")
**	En cas de premier TAB (current = NULL), on créer la liste
**	En cas de n-ième TAB, on passe au suivant
**	On modifie la commande avec la nouvelle suggestion
**	S'il y a un seul choix possible, on ajoute un ' ' ou un '/'
*/

void	do_completion(t_comp *comp, t_edit *edit)
{
	if (comp->cmd == NULL || *(comp->cmd) == 0)
		return ;
	get_word_to_complete(comp);
	comp_get_dir_to_open(comp, edit);
	if (comp->current == NULL)
		do_new_completion(comp, edit);
	else
		put_current_to_next(comp);
	if (comp->list)
		comp_modify_cmd(comp);
}
