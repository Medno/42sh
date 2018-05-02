/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 11:51:02 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/02 14:14:51 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			do_cd_home(t_init *init)
{
	int		ret;

	ret = 1;
	if (!ft_getenvloc(init, "HOME") ||
		ft_strequ(ft_getenvloc(init, "HOME"), ""))
		return (write(STDERR_FILENO, "cd: HOME not set\n", 17) ? 1 : 1);
	else if (!do_move(ft_getenvloc(init, "HOME"), init, 1))
		return (0);
	ft_printf_fd(2, "cd: %s: No such file or directory\n",
		ft_getenvloc(init, "HOME"));
	return (ret);
}

char		*ft_handle_cdpath(t_init *init, char *dir, int *do_print)
{
	char		**pathlist;
	char		*curpath;
	int			i;
	struct stat	info;

	i = -1;
	pathlist = ft_strsplit(ft_getenvloc(init, "CDPATH"), ':');
	curpath = NULL;
	while (pathlist && pathlist[++i])
	{
		curpath = paste_path(pathlist[i], dir);
		if (stat(curpath, &info) != -1)
			if (info.st_mode & S_IFDIR)
				break ;
		ft_strdel(&curpath);
	}
	if (!curpath)
		curpath = ft_strdup(dir);
	else
		*do_print = 1;
	ft_freetab(pathlist);
	return (curpath);
}

int			handle_cd_error(char *str)
{
	struct stat	stats;

	if (stat(str, &stats) < 0)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", str);
		return (1);
	}
	if (stats.st_mode & S_IFDIR)
	{
		if (!(S_IXUSR & stats.st_mode))
		{
			ft_printf_fd(STDERR_FILENO, "cd: %s: permission denied\n", str);
			return (1);
		}
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: Not a directory\n", str);
		return (1);
	}
	return (0);
}
