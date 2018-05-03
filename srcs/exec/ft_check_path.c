/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:07:47 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/03 14:58:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	**get_path(t_init *init)
{
	if (ft_getenv(&init->new_env, "PATH"))
		return (ft_strsplit(ft_getenv(&init->new_env, "PATH"), ':'));
	else
		return (ft_strsplit(ft_getenv(&init->loc_env, "PATH"), ':'));
}

int			check_bin(char *str, t_init *init, char **s_fin, int print)
{
	int		ret;
	int		i;
	char	*tmp;
	char	**path;

	path = NULL;
	tmp = NULL;
	path = get_path(init);
	i = -1;
	while (path && path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoindel(tmp, str);
		if (!(ret = check_slash(init, tmp, s_fin, NOPRINT)) || ret == -2)
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

int			check_path(char **arg, t_init *init, char **s_fin, int print)
{
	if (!arg || !*arg)
		return (1);
	if (is_builtin(*arg) || check_local(&arg, NOCLEAN))
	{
		*s_fin = NULL;
		return (0);
	}
	if (ft_strchr(*arg, '/'))
		return (check_slash(init, *arg, s_fin, print));
	else if (ft_getenv(&init->new_env, "PATH") ||
			ft_getenv(&init->loc_env, "PATH"))
		return (check_bin(*arg, init, s_fin, print));
	else
		return (check_error(-1, *arg, print));
}
