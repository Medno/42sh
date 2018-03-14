/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:07:47 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/14 09:40:50 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_error(int ret, char *str)
{
	if (ret == -1)
		ft_printf_fd(2, "42sh: %s: No such file or directory\n", str);
	else if (ret == -2)
		ft_printf_fd(2, "42sh: %s: Permission denied\n", str);
	else if (ret == -3)
		ft_printf_fd(2, "42sh: %s: is a directory\n", str);
	return (ret);
}

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

int		check_slash(char *str, char **s_fin)
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
	return (ret ? check_error(ret, str) : ret);
}


int		check_path(char *str, t_env **env, char **s_fin)
{
	if (!str)
		return (1);
	if (is_builtin(str))
	{
		*s_fin = NULL;
		return (0);
	}
	if (ft_strchr(str, '/'))
		return (check_slash(str, s_fin));
	else if (ft_getenv(env, "PATH"))
		return (check_bin(str, env, s_fin));
	else
		return (check_error(-1, str));
}
