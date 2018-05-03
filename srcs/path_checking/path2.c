/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:40:00 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/03 15:18:09 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*pathlist_to_str(t_path *pathlist)
{
	t_path	*tmp;
	char	*str;

	str = NULL;
	if (!pathlist)
		str = ft_strdup("/");
	else
	{
		tmp = pathlist;
		while (tmp)
		{
			if (!str)
				str = ft_strjoin("/", tmp->s);
			else
			{
				str = ft_strjoindel(str, "/");
				str = ft_strjoindel(str, tmp->s);
			}
			tmp = tmp->next;
		}
	}
	return (str);
}

static void	set_perms_type(t_init *init, t_path *elem, char *s)
{
	int			res_stat;
	struct stat	info;

	res_stat = stat(s, &info);
	if (ft_strequ(elem->s, ft_strrchr(init->pwd, '/') + 1) && res_stat < 0
			&& elem->next && ft_strequ(elem->next->s, ".."))
		elem->type = 'd';
	else if (res_stat < 0)
		elem->perms = 0;
	else
	{
		if (info.st_mode & S_IFDIR)
			elem->type = 'd';
		else
			elem->type = 'r';
		if (info.st_mode & S_IRUSR)
			elem->perms |= 1;
		else
			elem->perms |= 4;
		if (info.st_mode & S_IXUSR)
			elem->perms |= 2;
		else
			elem->perms |= 8;
	}
}

static void	el_checking(t_path *tmp, char **s, char **t)
{
	if (tmp->next && ft_strequ(tmp->next->s, ".."))
	{
		if (*s)
		{
			*t = ft_strjoin(*s, "/");
			*t = ft_strjoindel(*t, tmp->s);
		}
		else
			*t = ft_strjoin("/", tmp->s);
	}
	else
	{
		if (!*s)
			*s = ft_strjoin("/", tmp->s);
		else
		{
			*s = ft_strjoindel(*s, "/");
			*s = ft_strjoindel(*s, tmp->s);
		}
	}
}

void		set_path_info(t_init *init, t_path *pathlist)
{
	t_path	*tmp;
	char	*s;
	char	*t;

	s = NULL;
	t = NULL;
	tmp = pathlist;
	while (tmp)
	{
		if (ft_strequ(tmp->s, "..") && s)
			s = ft_strsubdel(s, 0, go_to_last(s, '/'));
		(!ft_strequ(tmp->s, "..")) ? el_checking(tmp, &s, &t) : 0;
		if (t)
			set_perms_type(init, tmp, t);
		else if (s)
			set_perms_type(init, tmp, s);
		tmp = (t && tmp->next && ft_strequ(tmp->next->s, "..")) ?
			tmp->next : tmp;
		ft_strdel(&t);
		tmp = tmp->next;
	}
	ft_strdel(&s);
}

void		remove_elem(t_path *elem, t_path **orig)
{
	t_path	*tmp;
	t_path	*tmp2;

	tmp = elem->prev;
	tmp2 = elem->next;
	ft_strdel(&elem->s);
	if (tmp || tmp2)
		ft_memdel((void **)&elem);
	if (!tmp && !tmp2)
		ft_memdel((void **)orig);
	else if (!tmp)
	{
		tmp2->prev = NULL;
		*orig = tmp2;
	}
	else if (!tmp2)
		tmp->next = NULL;
	else
	{
		tmp->next = tmp2;
		tmp2->prev = tmp;
	}
}
