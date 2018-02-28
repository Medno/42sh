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
//	str = [Dir/Dir/][Truc a completer] = [ret = suffix][ptr]
	if (ptr)
	{
		ret = ft_strsub(comp->str, 0, ft_strlen(comp->str) - ft_strlen(ptr));
		comp_modify_str(comp, ptr);
	}
//	Pas de '/' donc str = [Truc a completer]
	else
		ret = ft_strnew(0);
	return (ret);
}

static char	*get_absolute_path(t_comp *comp)
{
	char	*ptr;
	char	*ret;

	ptr = comp_go_to_last_slash(comp->str);
	ret = ft_strsub(comp->str, 0, ft_strlen(comp->str) - ft_strlen(ptr + 1));
	comp_modify_str(comp, ptr);
	return (ret);
}

void		comp_get_dir_to_open(t_comp *comp)
{
	char *cwd;
	char *suffix;

	if (comp->str && *(comp->str) && *(comp->str) == '/')
	{
		ft_printf("do_A\n");
		comp->dir = get_absolute_path(comp);
	}
	else
	{
		if (comp_has_slash(comp->str) == 1)
		{
			ft_printf("do_B\n");
			cwd = NULL;
			cwd = getcwd(cwd, 0);
			suffix = get_path_suffix(comp);
			comp->dir = ft_strjoin_infinite(3, cwd, "/", suffix);
			ft_strdel(&cwd);
			ft_strdel(&suffix);
		}
		ft_printf("do_C\n");
	}
}