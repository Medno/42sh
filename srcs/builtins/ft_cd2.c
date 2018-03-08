/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 08:17:18 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/08 11:42:35 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	test_err(char *str, char *dir, char **arr, int i)
{
	struct stat	info;
	int			check;

	check = 0;
	if (stat(str, &info) < 0 && (check = -1))
		ft_printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", dir);
	else if (!(info.st_mode & S_IFDIR) && (check = -1))
		ft_printf_fd(STDERR_FILENO, "cd: %s: Not a directory\n", dir);
	else if (!(S_IXUSR & info.st_mode) && !ft_strequ(arr[i + 1], "..")
			&& (check = -1))
		ft_printf_fd(STDERR_FILENO, "cd: %s: Permission denied\n", dir);
	if (check)
	{
		ft_freetab(arr);
		ft_strdel(&str);
	}
	return (check + 1);
}

static char	**paste_2(char **arr, char **test, char **new, int i)
{
	char	**tmp_tab;

	tmp_tab = arr;
	arr = delete_and_paste(arr, i);
	ft_memdel((void **)&tmp_tab);
	ft_strdel(test);
	ft_strdel(new);
	return (arr);
}

static char	*paste(char **arr, char *new, char *dir)
{
	int		i;
	char	*test;

	i = -1;
	test = NULL;
	while (arr[++i])
	{
		if (!ft_strequ(arr[i], "..") && !ft_strequ(arr[i], ".") &&
				(test = paste_strs(test, arr[i])))
			if (!(test_err(test, dir, arr, i)))
			{
				ft_strdel(&new);
				return (NULL);
			}
		if (ft_strequ(arr[i], "..") && (arr = paste_2(arr, &test, &new, i)))
			i = -1;
		else if (!ft_strequ(arr[i], "."))
			new = paste_strs(new, arr[i]);
	}
	if (!new)
		new = ft_strdup("/");
	ft_strdel(&test);
	ft_freetab(arr);
	return (new);
}

static char	*clear_path(char **curpath, char *dir)
{
	char	**arr;
	char	*new_path;

	new_path = NULL;
	if (!(arr = ft_strsplit(*curpath, '/')))
	{
		ft_strdel(curpath);
		return ("/");
	}
	ft_strdel(curpath);
	return (new_path = paste(arr, new_path, dir));
}

int			ft_cd_l(t_env **env, char *curpath, char *dir)
{
	char	*tmp;
	char	*tmp2;
	char	*path;

	tmp2 = NULL;
	if (curpath[0] != '/')
	{
		tmp = curpath;
		if (ft_getenv(env, "PWD"))
			tmp2 = ft_strdup(ft_getenv(env, "PWD"));
		else
			tmp2 = getcwd(tmp2, PATH_MAX);
		curpath = paste_path(tmp2, curpath);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	if (!(path = clear_path(&curpath, dir)))
		return (0);
	chdir(path);
	ft_setenv(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_setenv(env, "PWD", path);
	ft_strdel(&path);
	return (0);
}
