/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 08:17:18 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/18 09:29:58 by pchadeni         ###   ########.fr       */
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
		if (ft_strequ("..", tmp->s))
			tmp = handle_remove(tmp, pathlist);
		else if (tmp->perms & 4)
		{
			if (!(tmp->next && (ft_strequ("..", tmp->next->s))))
				return (error_cd(1, str));
		}
		else if (tmp->type == 'r')
			return (error_cd(2, str));
		else if (!tmp->type)
			return (error_cd(3, str));
		tmp = (!tmp) ? *pathlist : tmp->next;
	}
	return (0);
}

static char		*clear_path(t_init *init, char *s1, char *dir)
{
	t_path	*pathlist;
	t_path	*tmp;
	char	*new;

	new = NULL;
	if (!(pathlist = new_pathlist(s1)))
		return (ft_strdup("/"));
	tmp = pathlist;
	while (tmp)
	{
		if (ft_strequ(".", tmp->s))
			tmp = handle_remove(tmp, &pathlist);
		tmp = (!tmp) ? pathlist : tmp->next;
	}
	set_path_info(init, pathlist);
	if (check_elements(&pathlist, dir))
	{
		free_pathlist(&pathlist);
		return (NULL);
	}
	new = pathlist_to_str(pathlist);
	free_pathlist(&pathlist);
	return (new);
}

int				ft_cd_l(t_init *init, char *curpath, char *dir)
{
	char	*tmp2;
	char	*path;

	tmp2 = NULL;
	if (curpath[0] != '/')
		tmp2 = paste_path(init->pwd, curpath);
	if (!tmp2 && curpath)
		tmp2 = ft_strdup(curpath);
	if (!(path = clear_path(init, tmp2, dir)))
	{
		ft_strdel(&tmp2);
		return (1);
	}
	chdir(path);
	ft_setenv(&init->new_env, "OLDPWD", init->pwd);
	ft_setenv(&init->new_env, "PWD", path);
	ft_strdel(&init->pwd);
	init->pwd = ft_strdup(path);
	ft_strdel(&path);
	ft_strdel(&tmp2);
	return (0);
}
