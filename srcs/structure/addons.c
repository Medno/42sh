/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:50:29 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/17 14:09:21 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		put_path(t_init *init)
{
	char	*new;
	char	*tmp;
	int		len;

	new = ft_strdup(init->pwd);
	if (ft_getenv(&init->new_env, "HOME")
		&& ft_strstr(new, ft_getenv(&init->new_env, "HOME")))
	{
		tmp = ft_strdup(&new[ft_strlen(ft_getenv(&init->new_env, "HOME"))]);
		free(new);
		new = ft_strjoin("~", tmp);
		ft_strdel(&tmp);
	}
	ft_printf_fd(STDERR_FILENO, "{tblue}%s{eoc} {tgreen}$>{eoc} ", new);
	len = ft_strlen(new) + 4;
	ft_strdel(&new);
	return (len);
}

void	insert_env_start(t_env **env)
{
	char	*tmp;

	tmp = NULL;
	ft_setenv(env, "CLICOLOR", "1");
	if (!ft_getenv(env, "PWD"))
	{
		tmp = getcwd(tmp, PATH_MAX);
		ft_setenv(env, "PWD", tmp);
		ft_strdel(&tmp);
	}
	if (!ft_getenv(env, "SHLVL"))
		ft_setenv(env, "SHLVL", "1");
	else
	{
		tmp = ft_itoa(ft_atoi(ft_getenv(env, "SHLVL")) + 1);
		ft_setenv(env, "SHLVL", tmp);
		ft_strdel(&tmp);
	}
}
