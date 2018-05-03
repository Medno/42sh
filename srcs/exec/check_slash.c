/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_slash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:47:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/03 14:57:39 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_path	*handle_remove(t_path *tmp, t_path **pathlist)
{
	t_path	*tmp2;

	if (ft_strequ(".", tmp->s) || (ft_strequ("..", tmp->s) && !tmp->prev))
		remove_elem(tmp, pathlist);
	else
	{
		tmp2 = tmp->prev;
		remove_elem(tmp2, pathlist);
		remove_elem(tmp, pathlist);
	}
	return (*pathlist);
}

static int		check_valid(t_path **pathlist)
{
	t_path	*tmp;

	tmp = *pathlist;
	while (tmp)
	{
		if (ft_strequ(".", tmp->s) || ft_strequ("..", tmp->s))
			tmp = handle_remove(tmp, pathlist);
		else if (tmp->type == 'd')
		{
			if (tmp->perms & 4 && tmp->next)
				return (-2);
			if (!tmp->next)
				return (-3);
		}
		else if (tmp->type == 'r' && !tmp->next)
		{
			if (tmp->perms & 8)
				return (-2);
		}
		else if (!tmp->perms)
			return (-1);
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

static int		check_str(char *str)
{
	while (*str)
	{
		if (*str != '/')
			return (0);
		str++;
	}
	return (1);
}

int				check_slash(t_init *init, char *str, char **s_fin, int print)
{
	int		ret;
	char	*tmp;
	char	*cwd;
	t_path	*pathlist;

	cwd = NULL;
	if (check_str(str))
		return (check_error(-3, str, print));
	if (*str != '/')
	{
		cwd = getcwd(cwd, PATH_MAX);
		tmp = paste_path(cwd, str);
		ft_strdel(&cwd);
	}
	else
		tmp = ft_strdup(str);
	pathlist = new_pathlist(tmp);
	ft_strdel(&tmp);
	set_path_info(init, pathlist);
	ret = check_valid(&pathlist);
	if (!ret)
		*s_fin = pathlist_to_str(pathlist);
	free_pathlist(&pathlist);
	return (ret ? check_error(ret, str, print) : ret);
}
