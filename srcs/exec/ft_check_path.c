/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:07:47 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/19 10:51:33 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_bin(char *str, t_env **env, char **s_fin, int print)
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
		if (!(ret = check_slash(tmp, s_fin, NOPRINT)) || ret == -2)
			break ;
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	ft_freetab(path);
	if (ret == -2)
		return (check_error(ret, str, print));
	else if (ret)
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
		return (check_bin(*arg, env, s_fin, print));
	else
		return (check_error(-1, *arg, print));
}
