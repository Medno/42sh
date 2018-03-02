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

void	comp_modify_cmd(t_comp *comp)
{
	char *prefix;
	char *suffix;

//	cmd = [prefix][dir][string[]][suffixe]
//	ft_printf("CMD = [%s]\n", comp->cmd);
//	ft_printf("dir = [%s]\n", comp->dir);
//	ft_printf("comp_str = [%s]\n", comp->str);
//	prefix = ft_strsub(comp->cmd, 0, comp->pos - 1 - ft_strlen(comp->str) - ft_strlen(comp->dir));
	prefix = ft_strsub(comp->cmd, 0, comp->pos - 1 - ft_strlen(comp->str));
//	ft_printf("prefix = [%s]\n", prefix);
	suffix = ft_strsub(comp->cmd, comp->pos - 1, ft_strlen(comp->cmd) - comp->pos + 1);
//	ft_printf("suffix = [%s]\n", suffix);


//	ft_printf("\n On va modifier [%s] par [%s]\n", comp->str, comp->current->cmd);

// On avance le curseur à la fin du current
//	ft_printf("On recule pos de [%d]\n", ft_strlen(comp->str));
	comp->pos -= ft_strlen(comp->str);
//	ft_printf("On avance pos de [%d]\n", ft_strlen(comp->current->cmd));
	comp->pos += ft_strlen(comp->current->cmd);
//	ft_printf("[%s]", prefix);
//	ft_printf("[%s]", comp->dir);
//	ft_printf("[%s]", comp->str);
//	ft_printf("[%s]\n", suffix);

//	cmd = (commande à comp)([l]etionner)
//	ft_printf("\nA terme, cmd = [%s]\n", ft_strjoin_infinite(3, prefix, comp->current->cmd, suffix));
	if (comp->cmd)
		ft_strdel(&(comp->cmd));
	comp->cmd = ft_strjoin_infinite(3, prefix, comp->current->cmd, suffix);
}

void	comp_modify_cur_string_for_display(t_comp *comp)
{
	char *ptr;
	char *tmp;

	ptr = comp_go_to_last_slash(comp->str);
	if (ptr)
	{
		tmp = comp->str;
		comp->str = ft_strdup(ptr + 1);
		ft_strdel(&tmp);
	}
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

// void	comp_validate_choice(t_comp *comp)
// {
// 	char *str;

// 	str = get_word_to_complete(comp);
// // CAS DIR
// 	if (comp_is_cmd(comp, str) == 0 && comp_is_directory(comp))
// 	{
// 		comp->cmd = ft_strjoindel(comp->cmd, "/");
// 		comp->pos++;
// 	}
// // CAS Commande OU Fichier
// 	else
// 	{
// 		comp->cmd = ft_strjoindel(comp->cmd, " ");
// 		comp->pos++;
// 	}
// 	ft_strdel(&str);
// 	reset_completion(comp);
// }

/*
**	Si on est sur le premier mot et qu'il n'y a pas de '/', on analyse les executables du PATH
**	Si on est sur le premier mot et qu'il y a un '/', on analyse les dossiers et executables du dossier visé
**	Si on est pas sur le premier mot, on analyse les dossiers et fichiers du dossier visé
**	On initialise current au début de la liste
*/

void	do_new_completion(t_comp *comp)
{
	if (comp_is_first_word(comp) == 1)
	{
		if (comp->dir)
		{
//			ft_printf("do_1\n");
			comp_get_pot_dir_exec(comp);
		}
		else
		{
//			ft_printf("do_2\n");
			comp_get_pot_cmd(comp);
		}
	}
	else
	{
//		ft_printf("do_3\n");
		comp_get_pot_dir(comp);
	}

	t_lcomp *tmp = comp->list;
//	while (tmp) { ft_printf("[%s]-> ", tmp->cmd); tmp = tmp->next; }
//	ft_putchar('\n');
//	ft_putchar('A');
//	comp_sort_alphab(comp);	ft_putchar('B');
//	comp_check_duplicate(comp);	ft_putchar('C');
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
**	On recuperer la string à completer
**	En cas de premier TAB (current = NULL), on créer la liste
**	En cas de n-ième TAB, on passe au suivant
**	On modifie la commande par la nouvelle suggestion
**	S'il y a un seul choix, on ajoute un ' ' ou un '/'
*/

void	do_completion(t_comp *comp, t_env *env)
{
	if (comp->cmd == NULL || *(comp->cmd) == 0)
		return ;

	(void)env;
//	ft_printf("\nEn entree :\n");
//	ft_printf("cmd = [%s]\npos = [%d]\n", comp->cmd, comp->pos);
//	ft_printf("current = [%s]\n list = [%s]\n", comp->current->cmd, comp->list->cmd);
	
	get_word_to_complete(comp);
	
//	ft_printf("\nApres get word : ");
//	ft_printf("dir = [%s]\nstring = [%s]\n", comp->dir, comp->str);
	
	comp_get_dir_to_open(comp);
	
//	ft_printf("\nApres get dir : ");
//	ft_printf("dir = [%s]\nstring = [%s]\n", comp->dir, comp->str)
	;
	if (comp->current == NULL)
		do_new_completion(comp);
	else
		put_current_to_next(comp);

//	ft_printf("\nApres new_comp : ");
//	if (comp->current && comp->list)
//	ft_printf("current = [%s]\n list = [%s]\n", comp->current->cmd, comp->list->cmd);
// On modifie remplace str par current dans cmd si on a reussit a remplir pot_list
	if (comp->list)
		comp_modify_cmd(comp);

//	Si on a un seul choix, on valide et on met current à NULL
	// if (comp->current && comp->current->next == NULL
	// 	&& comp->current == comp->list)
	// 	comp_validate_choice(comp);
}















