/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:40:00 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/17 20:43:33 by kyazdani         ###   ########.fr       */
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

static void	set_perms_type(t_path *elem, char *s)
{
	struct stat	info;

	if (stat(s, &info) < 0)
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

void		set_path_info(t_path *pathlist)
{
	t_path	*tmp;
	char	*s;

	tmp = pathlist;
	s = NULL;
	while (tmp)
	{
		if (!s)
			s = ft_strjoin("/", tmp->s);
		else
		{
			s = ft_strjoindel(s, "/");
			s = ft_strjoindel(s, tmp->s);
		}
		set_perms_type(tmp, s);
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
