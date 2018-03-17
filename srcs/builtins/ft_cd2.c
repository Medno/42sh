/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 08:17:18 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/17 17:39:17 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*clear_path(char *s1)
{
	t_path	*pathlist;
	char	*new;

	if (!(pathlist = new_pathlist(s1)))
		return (s1);
	if (check_elements(pathlist, &new))
		return (NULL);
	free_pathlist(&pathlist);
	return (new);
}

int			ft_cd_l(t_env **env, char *curpath)
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
		tmp2 = paste_path(tmp2, curpath);
		ft_strdel(&curpath);
		curpath = ft_strdup(tmp2);
		ft_strdel(&tmp2);
	}
	ft_printf("[%s]\n", curpath);
	if (!(path = clear_path(curpath)))
		return (1);
	ft_strdel(&curpath);
	chdir(path);
	ft_setenv(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_setenv(env, "PWD", path);
	ft_strdel(&path);
	return (0);
}
