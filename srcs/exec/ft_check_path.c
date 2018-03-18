/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:07:47 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/18 10:50:22 by kyazdani         ###   ########.fr       */
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

	path = NULL;
	tmp = NULL;
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

int			check_path(char **arg, t_env **env, char **s_fin, int print)
{
	if (!arg || !*arg)
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
