/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 08:17:18 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/26 15:28:26 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		error_cd(int nb, char *str)
{
	if (nb == 1)
		ft_printf_fd(STDERR_FILENO, "cd: %s: permission denied\n", str);
	else if (nb == 2)
		ft_printf_fd(STDERR_FILENO, "cd: %s: Not a directory\n", str);
	else if (nb == 3)
		ft_printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", str);
	return (1);
}

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
	return (NULL);
}

static int		check_elements(t_path **pathlist, char *str)
{
	t_path	*tmp;

	tmp = *pathlist;
	while (tmp)
	{
		if (tmp->perms & 4)
		{
			if (tmp->next && ft_strequ("..", tmp->next->s))
				tmp = tmp->next;
			else
				return (error_cd(1, str));
		}
		else if (tmp->type == 'r')
			return (error_cd(2, str));
		else if (!tmp->type)
			return (error_cd(3, str));
		if (ft_strequ(".", tmp->s) || ft_strequ("..", tmp->s))
			tmp = handle_remove(tmp, pathlist);
		if (!tmp)
			tmp = *pathlist;
		else
			tmp = tmp->next;
	}
	return (0);
}

static char		*clear_path(char *s1, char *dir)
{
	t_path	*pathlist;
	char	*new;

	new = NULL;
	if (!(pathlist = new_pathlist(s1)))
	{
		ft_strdel(&s1);
		return (ft_strdup("/"));
	}
	ft_strdel(&s1);
	set_path_info(pathlist);
	if (check_elements(&pathlist, dir))
	{
		free_pathlist(&pathlist);
		return (NULL);
	}
	new = pathlist_to_str(pathlist);
	free_pathlist(&pathlist);
	return (new);
}

int				ft_cd_l(t_env **env, char *curpath, char *dir)
{
	char	*tmp;
	char	*tmp2;
	char	*path;

	tmp = NULL;
	if (curpath[0] != '/')
	{
		tmp = ft_getenv(env, "PWD") ? ft_strdup(ft_getenv(env, "PWD")) 
				: getcwd(tmp, PATH_MAX);
		tmp2 = paste_path(tmp, curpath);
		ft_strdel(&curpath);
		ft_strdel(&tmp);
		curpath = ft_strdup(tmp2);
		ft_strdel(&tmp2);
	}
	if (!(path = clear_path(curpath, dir)))
		return (1);
	chdir(path);
	ft_setenv(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_setenv(env, "PWD", path);
	ft_strdel(&path);
	return (0);
}
