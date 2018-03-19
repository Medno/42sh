/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_cmd.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2017/02/20 18:20:51 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void		comp_modify_str(t_comp *comp, char *ptr)
{
	char *tmp;

	tmp = comp->str;
	comp->str = ft_strdup(ptr + 1);
	ft_strdel(&tmp);
}

static char		*get_path_suffix(t_comp *comp)
{
	char *ptr;
	char *ret;

	ptr = comp_go_to_last_slash(comp->str);
	if (ptr)
	{
		ret = ft_strsub(comp->str, 0, ft_strlen(comp->str) - ft_strlen(ptr) + 1);
		comp_modify_str(comp, ptr);
	}
	else
		ret = ft_strnew(0);
	return (ret);
}

static char		*get_absolute_path(t_comp *comp)
{
	char	*ptr;
	char	*ret;

	ptr = comp_go_to_last_slash(comp->str);
	ret = ft_strsub(comp->str, 0, ft_strlen(comp->str) - ft_strlen(ptr + 1));
	comp_modify_str(comp, ptr);
	return (ret);
}

/*
**	On veut isoler "[directory]" dans "[directory][string to comp]" (Cas : "../dossier/comp[]")
**	1er cas : "/dossier/dossier/comp", on cherche le chemin absolue du comp
**	2eme cas : "ls dossier/dossier/comp", on cherche le chemin relatif en fonction du cwd
**	3eme cas : "dossier/dossier/comp", on remplit dir par '\0' pour reperer le cas premier mot
**	4eme cas : "ls comp", pas besoin de remplir dir on cherchera le cwd
*/

void			comp_get_dir_to_open(t_comp *comp)
{
	char *cwd;
	char *suffix;

	if (comp->str && *(comp->str) && *(comp->str) == '/')
		comp->dir = get_absolute_path(comp);
	else
	{
		if (comp_has_slash(comp->str) == 1 || comp_is_first_word(comp) == 0)
		{
			cwd = NULL;
			cwd = getcwd(cwd, 0);
			suffix = get_path_suffix(comp);
			comp->dir = ft_strjoin_infinite(3, cwd, "/", suffix);			
//			ft_printf("HELLO DIR = [%s]+['/']+[%s]\n", cwd, suffix);
			ft_strdel(&cwd);
			ft_strdel(&suffix);
//			ft_printf("HELLO DIR = [%s]\n", comp->dir);
		}
	}
}