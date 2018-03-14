/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:07:47 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/14 14:48:07 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	is_accessible(char *str)
{
	struct stat	buf;

	if (!access(str, F_OK))
	{
		if (!lstat(str, &buf))
		{
			if (S_IFREG & buf.st_mode)
			{
				if (S_IXUSR & buf.st_mode)
					return (0);
				return (-2);
			}
			return (-3);
		}
		return (-2);
	}
	return (-1);
}

static int	check_bin(char *str, t_env **env, char **s_fin)
{
	int		ret;
	int		i;
	char	*tmp;
	char	**path;

	path = ft_strsplit(ft_getenv(env, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoindel(tmp, str);
		if (!(ret = is_accessible(tmp)))
		{
			*s_fin = ft_strdup(tmp);
			break ;
		}
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	ft_freetab(path);
	if (ret)
		ret = 1;
	return (ret);
}

int			check_slash(char *str, char **s_fin, int print)
{
	int		i;
	int		ret;
	char	**path;

	i = -1;
	if (!(ret = is_accessible(str)))
	{
		*s_fin = ft_strdup(str);
		return (0);
	}
	path = ft_strsplit(str, '/');
	if (*str == '/')
		*s_fin = ft_strdup("/");
	while (path[++i])
	{
		if (*s_fin)
			*s_fin = ft_strjoindel(*s_fin, path[i]);
		else
			*s_fin = ft_strdup(path[i]);
		if (!(ret = is_accessible(*s_fin)) || (ret == -1))
			break ;
		*s_fin = ft_strjoindel(*s_fin, "/");
	}
	ft_freetab(path);
	return (ret ? check_error(ret, str, print) : ret);
}

int			check_path(char **arg, t_env **env, char **s_fin, int print)
{
	if (!*arg)
		return (1);
	if (is_builtin(*arg) || check_local(&arg, NOCLEAN))
	{
		*s_fin = NULL;
		return (0);
	}
	if (ft_strchr(*arg, '/'))
		return (check_slash(*arg, s_fin, print));
	else if (ft_getenv(env, "PATH"))
		return (check_bin(*arg, env, s_fin));
	else
		return (check_error(-1, *arg, print));
}
