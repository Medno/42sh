/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_get_dir_to_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:50:52 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:50:55 by hfouques         ###   ########.fr       */
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
		ret = ft_strsub(comp->str, 0,
			ft_strlen(comp->str) - ft_strlen(ptr) + 1);
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
**	On veut isoler "[dir]" dans "[dir][str to comp]" (Cas : "../dossier/comp[]")
**	1er cas : "/dossier/dossier/comp", on cherche le chemin absolue du comp
**	2eme cas : "ls dos/dos/comp", on cherche le chemin relatif en fct du cwd
**	3eme cas : "dos/dos/comp", on remplit dir par '\0' pour le cas 1er mot
**	4eme cas : "ls comp", pas besoin de remplir dir on cherchera le cwd
*/

void			comp_get_dir_to_open(t_comp *comp, t_edit *edit)
{
	char *cwd;
	char *suffix;

	if (comp->str && *(comp->str) && *(comp->str) == '~')
		add_tild_in_str(comp, edit);
	if (comp->str && ft_strchr(comp->str, '$'))
		add_dollar_in_str(comp, edit);
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
			ft_strdel(&cwd);
			ft_strdel(&suffix);
		}
	}
}
