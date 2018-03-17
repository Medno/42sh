/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 08:17:18 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/17 16:02:32 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*clear_path(char *s1, char *s2);

int			ft_cd_l(t_env **env, char *curpath, char *dir)
{
	char	*tmp2;
	char	*path;

	tmp2 = NULL;
	if (curpath[0] != '/')
	{
		if (ft_getenv(env, "PWD"))
			tmp2 = ft_strdup(ft_getenv(env, "PWD"));
		else
			tmp2 = getcwd(tmp2, PATH_MAX);
		curpath = paste_path(tmp2, curpath);
	}
	ft_printf("[%s] [%s]\n", curpath, dir);
	ft_strdel(&curpath);
//	if (!(path = clear_path(curpath, dir)))
//		return (1);
//	chdir(path);
//	ft_setenv(env, "OLDPWD", ft_getenv(env, "PWD"));
//	ft_setenv(env, "PWD", path);
//	ft_strdel(&path);
	return (0);
}
