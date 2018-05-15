/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:31:24 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/15 11:28:47 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int		g_optind;

static int		swap_pwd(t_init *init)
{
	ft_setenv(&init->new_env, "PWD", ft_getenvloc(init, "OLDPWD"));
	ft_setenv(&init->new_env, "OLDPWD", init->pwd);
	ft_strdel(&init->pwd);
	init->pwd = ft_strdup(ft_getenv(&init->new_env, "PWD"));
	return (0);
}

int				do_move(char *path, t_init *init, int p)
{
	char	*tmp;

	tmp = NULL;
	if (chdir(path) < 0)
		return (1);
	if (!p && ft_strequ(path, ft_getenvloc(init, "OLDPWD")))
		swap_pwd(init);
	else
	{
		ft_setenv(&init->new_env, "OLDPWD", init->pwd);
		if ((tmp = getcwd(tmp, PATH_MAX)))
		{
			ft_setenv(&init->new_env, "PWD", tmp);
			ft_strdel(&init->pwd);
			init->pwd = tmp;
		}
		else
			return (ft_printf("cd: error retrieving current directory\n"));
	}
	return (0);
}

int				ft_getopt_cd(char **entry, int *do_print)
{
	int c;
	int opt_p;

	*do_print = 0;
	c = 0;
	opt_p = 0;
	reset_ft_opt();
	while ((c = ft_getopt(ft_tablen(entry), entry, "LP")) != -1)
	{
		if (c == '?')
			return (write(STDERR_FILENO, "cd: usage: cd [-LP] [dir]\n",
				26) ? -1 : -1);
		else if (c == 'P')
			opt_p = 1;
		else if (c == 'L')
			opt_p = 0;
	}
	return (opt_p);
}

char			*get_curpath(t_init *init, char *dir, int *do_print)
{
	char	*curpath;

	if (!ft_getenvloc(init, "CDPATH") || ft_strnequ("./", dir, 2)
		|| *dir == '/' || ft_strnequ("../", dir, 3)
		|| ft_strequ(".", dir) || ft_strequ("..", dir))
		curpath = ft_strdup(dir);
	else
		curpath = ft_handle_cdpath(init, dir, do_print);
	return (curpath);
}

int				ft_cd(t_init *init, char ***entry)
{
	int		opt_p;
	char	*curpath;
	int		ret;
	int		do_print;

	if ((opt_p = ft_getopt_cd(*entry, &do_print)) == -1)
		return (1);
	if (!((*entry)[g_optind]))
		return (do_cd_home(init));
	if (ft_strequ((*entry)[g_optind], "-"))
	{
		if (!ft_getenvloc(init, "OLDPWD"))
			return (write(STDERR_FILENO, "cd: OLDPWD not set\n", 19) ? 1 : 1);
		ft_strdel(&(*entry)[g_optind]);
		(*entry)[g_optind] = ft_strdup(ft_getenvloc(init, "OLDPWD"));
		do_print = 1;
	}
	curpath = get_curpath(init, (*entry)[g_optind], &do_print);
	if (opt_p)
		ret = do_move(curpath, init, 1) ? handle_cd_error(curpath) : 0;
	else
		ret = ft_cd_l(init, curpath, (*entry)[g_optind]);
	do_print && !ret ? ft_printf("%s\n", init->pwd) : 0;
	ft_strdel(&curpath);
	return (ret);
}
