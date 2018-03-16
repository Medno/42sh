/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:37:15 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/15 16:32:13 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*copy_home(t_init *init)
{
	if (!ft_getenv(&init->new_env, "HOME"))
		return (ft_strdup("/Users"));
	return (ft_strdup(ft_getenv(&init->new_env, "HOME")));
}

char	*pwd_tilde(t_init *init, char c)
{
	if (c == '+')
		return (ft_strdup(ft_getenv(&init->new_env, "PWD")));
	if (c == '-')
		return (ft_strdup(ft_getenv(&init->new_env, "OLDPWD")));
	return (NULL);
}

int		check_prefix(t_init *init, char *str, char buf[], int *i)
{
	int		res;
	char	*tmp;

	while (str[*i] && str[*i] != '/')
	{
		buf[*i - 1] = str[*i];
		(*i)++;
	}
	res = 0;
	if (!buf[1] && (buf[0] == '-' || buf[0] == '+'))
	{
		if ((buf[0] == '-' && !ft_getenv(&init->new_env, "OLDPWD")) ||
				(buf[0] == '+' && !ft_getenv(&init->new_env, "PWD")))
			res = 1;
	}
	else if (buf[0])
	{
		tmp = ft_strjoin("/Users/", buf);
		if (access(tmp, F_OK) != 0)
			res = 1;
		ft_strdel(&tmp);
	}
	return (res);
}

char	*exp_tilde(t_init *init, char *str, int len)
{
	int		i;
	char	buf[len + 1];
	char	*res;

	i = 1;
	if (!str[1])
	{
		ft_strdel(&str);
		return (copy_home(init));
	}
	ft_bzero(buf, len);
	if (check_prefix(init, str, buf, &i))
		return (str);
	if (i != 1 && !ft_strequ(buf, "+") && !ft_strequ(buf, "-"))
		res = ft_strjoin("/Users/", buf);
	else if (i != 1)
		res = pwd_tilde(init, str[1]);
	else
		res = copy_home(init);
	if (str[i] == '/')
		res = ft_strjoindel(res, &str[i]);
	ft_strdel(&str);
	return (res);
}
