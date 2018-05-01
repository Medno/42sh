/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:31:24 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/27 09:48:28 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int		g_optind;

static int		do_move(char *path, t_init *init, int p)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_getenvloc(init, "PWD"))
	{
		tmp = getcwd(tmp, PATH_MAX);
		ft_setenv(&init->new_env, "PWD", tmp);
		ft_strdel(&tmp);
	}
	if (chdir(path) < 0)
		return (1);
	if (!p && ft_strequ(path, ft_getenvloc(init, "OLDPWD")))
	{
		tmp = ft_strdup(ft_getenvloc(init, "PWD"));
		ft_setenv(&init->new_env, "PWD", ft_getenvloc(init, "OLDPWD"));
		ft_setenv(&init->new_env, "OLDPWD", tmp);
	}
	else
	{
		ft_setenv(&init->new_env, "OLDPWD", ft_getenvloc(init, "PWD"));
		if ((tmp = getcwd(tmp, PATH_MAX)))
			ft_setenv(&init->new_env, "PWD", tmp);
		else
			return (ft_printf("cd: error retrieving current directory\n"));
	}
	ft_strdel(&tmp);
	return (0);
}

int				handle_cd_error(char *str)
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

static char		*ft_handle_cdpath(t_init *init, char *dir, int *do_print)
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

int				ft_getopt_cd(char **entry)
{
	int c;
	int opt_p;

	c = 0;
	opt_p = 0;
	reset_ft_opt();
	while ((c = ft_getopt(ft_tablen(entry), entry, "LP")) != -1)
	{
		if (c == '?')
			return (write(STDERR_FILENO, "cd: usage: cd[-LP] [dir]\n",
			 26) ? -1 : -1);
		else if (c == 'P')
			opt_p = 1;
		else if (c == 'L')
			opt_p = 0;
	}
	return (opt_p);
}

int				do_simple_cd(t_init *init, char *dir)
{
	if (!dir)
	{
		if (!ft_getenvloc(init, "HOME") || ft_strequ(ft_getenvloc(init, "HOME"), ""))
			return (write(STDERR_FILENO, "cd: HOME not set\n", 17) ? 1 : 1);
		else if (!do_move(ft_getenvloc(init, "HOME"), init, 1))
			return (0);
		else
			ft_printf_fd(2, "cd: %s: No such file or directory\n",	ft_getenvloc(init, "HOME"));
		return (1);
	}
	else
	{
		if (!ft_getenvloc(init, "OLDPWD") || ft_strequ(ft_getenvloc(init, "OLDPWD"), ""))
			return (write(2, "cd: OLDPWD not set\n", 19) ? 1 : 1);
		else if (!do_move(ft_getenvloc(init, "OLDPWD"), init, 0))
			return (!(ft_printf("%s\n", ft_getenv(&init->new_env, "PWD"))));
		else
			ft_printf_fd(2, "cd: %s: No such file or directory\n",	ft_getenvloc(init, "OLDPWD"));
		return (1);
	}
}

int				ft_cd(t_init *init, char ***entry)
{
	int		opt_p;
	char	*curpath;
	int		ret;
	int		do_print;

	if ((opt_p = ft_getopt_cd(*entry)) == -1)
		return (1);
	if (!((*entry)[g_optind]) || ft_strequ((*entry)[g_optind], "-"))
		return (do_simple_cd(init, (*entry)[g_optind]));
	do_print = 0;
	if (!ft_getenvloc(init, "CDPATH") || ft_strnequ("./", (*entry)[g_optind], 2) || *(*entry)[g_optind] == '/' || ft_strnequ("../", (*entry)[g_optind], 3)
		|| ft_strequ(".", (*entry)[g_optind]) || ft_strequ("..", (*entry)[g_optind]))
		curpath = ft_strdup((*entry)[g_optind]);
	else
		curpath = ft_handle_cdpath(init, (*entry)[g_optind], &do_print);
	if (opt_p)
		ret = do_move(curpath, init, 1) ? handle_cd_error(curpath) : 0;
	else
		ret = ft_cd_l(init, curpath, (*entry)[g_optind]);
	do_print ? ft_printf("%s\n", ft_getenv(&init->new_env, "PWD")) : 0;
	ft_strdel(&curpath);
	return (ret);
}

