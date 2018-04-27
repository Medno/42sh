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

static int		do_move(char *path, t_env **env, int p)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_getenv(env, "PWD"))
	{
		tmp = getcwd(tmp, PATH_MAX);
		ft_setenv(env, "PWD", tmp);
		ft_strdel(&tmp);
	}
	if (chdir(path) < 0)
		return (1);
	if (!p && ft_strequ(path, ft_getenv(env, "OLDPWD")))
	{
		tmp = ft_strdup(ft_getenv(env, "PWD"));
		ft_setenv(env, "PWD", ft_getenv(env, "OLDPWD"));
		ft_setenv(env, "OLDPWD", tmp);
	}
	else
	{
		ft_setenv(env, "OLDPWD", ft_getenv(env, "PWD"));
		tmp = getcwd(tmp, PATH_MAX);
		ft_setenv(env, "PWD", tmp);
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

static char		*ft_handle_cdpath(t_env **env, char *dir)
{
	char		**pathlist;
	char		*curpath;
	int			i;
	struct stat	info;

	i = -1;
	pathlist = ft_strsplit(ft_getenv(env, "CDPATH"), ':');
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
	ft_freetab(pathlist);
	return (curpath);
}

static int		ft_cd_2(t_init *init, char *dir, int p)
{
	char	*curpath;

	if (ft_strequ(dir, "-") && ft_getenv(&init->env_tmp, "OLDPWD"))
	{
		if (!do_move(ft_getenv(&init->env_tmp, "OLDPWD"), &init->new_env, 0))
			return (!(ft_printf("%s\n", ft_getenv(&init->env_tmp, "PWD"))));
		else if (ft_printf_fd(2, "cd: %s: No such file or directory\n",
					ft_getenv(&init->env_tmp, "OLDPWD")))
			return (1);
	}
	else if (ft_strequ(dir, "-") && write(2, "cd: OLDPWD not set\n", 19))
		return (1);
	if (!ft_getenv(&init->env_tmp, "CDPATH") ||
			(*dir == '.' && *(dir + 1) == '/') ||
	*dir == '/' || (*dir == '.' && *(dir + 1) == '.' && (*dir + 2) == '/') ||
	ft_strequ(".", dir) || ft_strequ("..", dir))
		curpath = ft_strdup(dir);
	else
		curpath = ft_handle_cdpath(&init->new_env, dir);
	if (p)
	{
		p = do_move(curpath, &init->new_env, 1) ? handle_cd_error(curpath) : 0;
		ft_strdel(&curpath);
		return (p);
	}
	return (ft_cd_l(&init->new_env, curpath, dir));
}

int				ft_cd(t_init *init, char ***entry)
{
	int		opt_p;
	int		c;

	opt_p = 0;
	c = 0;
	reset_ft_opt();
	while ((c = ft_getopt(ft_tablen(*entry), *entry, "LP")) != -1)
	{
		if (c == '?' && write(STDERR_FILENO, "cd: usage: cd [-LP] [dir]\n", 26))
			return (1);
		else if (c == 'P')
			opt_p = 1;
		else if (c == 'L')
			opt_p = 0;
	}
	if (!(*entry)[g_optind])
	{
		if ((!ft_getenv(&init->env_tmp, "HOME") ||
					ft_strequ(ft_getenv(&init->env_tmp, "HOME"), ""))
			&& write(STDERR_FILENO, "cd: HOME not set\n", 17))
			return (1);
		return (do_move(ft_getenv(&init->env_tmp, "HOME"), &init->new_env, 1));
	}
	else
		return (ft_cd_2(init, (*entry)[g_optind], opt_p));
}
