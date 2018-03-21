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
**	Cas "./comp[]" ou "/Dossier/comp[]", on analyse les dossiers et executables du dossier visé
**	Cas "comp[] args", on analyse les executables du PATH
**	Cas "command dossier/comp[]" on analyse les dossiers et fichiers du dossier visé
**	On vérifie l'ordre alphabetique, qu'il n'y a pas de duplicata et on ajoute les builtins
**	Comp->current prend la premiere valeur de la liste créee
*/

void	do_new_completion(t_comp *comp, t_edit *edit)
{
	if (comp_is_first_word(comp) == 1)
	{
		if (comp->dir)
			comp_get_pot_dir_exec(comp);
		else
			comp_get_pot_cmd(comp, edit);
	}
	else
		comp_get_pot_dir(comp);
	comp_sort_alphab(comp);
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
	suffix = ft_strsub(comp->cmd, comp->pos - 1, ft_strlen(comp->cmd) - comp->pos + 1);
	comp->pos -= ft_strlen(comp->str);
	comp->pos += ft_strlen(comp->current->cmd);
	if (comp->cmd)
		ft_strdel(&(comp->cmd));
	comp->cmd = ft_strjoin_infinite(3, prefix, comp->current->cmd, suffix);
	ft_strdel(&prefix);
	ft_strdel(&suffix);
}

int		comp_is_directory(t_comp *comp)
{
	struct	stat sb;
	int		ret;
	char	*file_path;

//	ft_printf("file_path = [%s] + [%s]\n", comp->dir, comp->current->cmd);
	file_path = ft_strjoin(comp->dir, comp->current->cmd);
// stat renvoie 0 en cas de succes
	if (stat(file_path, &sb) != 0)
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

void	comp_validate_choice(t_comp *comp)
{
//	Si on a un seul choix, on valide et on met current à NULL
	if (comp->list->next)
		return ;
// CAS DIR
	if (comp_is_directory(comp))
	{
		comp->current->cmd = ft_strjoindel(comp->current->cmd, "/");
		comp->pos++;
	}
// CAS Commande OU Fichier
	else
	{
		comp->current->cmd = ft_strjoindel(comp->current->cmd, " ");
		comp->pos++;
	}
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

	// ft_printf("\nEn entree :\n");
	// ft_printf("cmd = [%s]\npos = [%d]\n", comp->cmd, comp->pos);
	// if (comp->list)
	// 	ft_printf("current = [%s]\nlist = [%s]\n", comp->current->cmd, comp->list ? comp->list->cmd : 0);

	get_word_to_complete(comp);
	// ft_printf("\nApres get word : ");
	// ft_printf("dir = [%s]\nstring = [%s]\n", comp->dir, comp->str);

	comp_get_dir_to_open(comp);
	// ft_printf("\nApres get dir : ");
	// ft_printf("dir = [%s] string = [%s]\n", comp->dir, comp->str);

	if (comp->current == NULL)
		do_new_completion(comp, edit);
	else
		put_current_to_next(comp);
	// ft_printf("\nApres new_comp : ");
	// if (comp->current && comp->list)
	// 	ft_printf("current = [%s]\n list = [%s]\n", comp->current->cmd, comp->list->cmd);
	// else
	// 	ft_printf("\n");

	if (comp->list)
	{
		comp_modify_cmd(comp);
		comp_validate_choice(comp);
	}
}
