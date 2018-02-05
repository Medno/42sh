/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:50:29 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/31 13:45:21 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	put_path(t_env **env)
{
	char	*new;
	char	*tmp;

	new = NULL;
	if (ft_getenv(env, "PWD"))
		new = ft_strdup(ft_getenv(env, "PWD"));
	else if (!(new = getcwd(new, 4096)))
		new = ft_strdup("/");
	if (ft_getenv(env, "HOME") && ft_strstr(new, ft_getenv(env, "HOME")))
	{
		tmp = ft_strdup(&new[ft_strlen(ft_getenv(env, "HOME"))]);
		free(new);
		new = ft_strjoin("~", tmp);
		ft_strdel(&tmp);
	}
	ft_printf_fd(STDERR_FILENO, "{tblue}%s{eoc} {tgreen}$>{eoc} ", new);
	ft_strdel(&new);
}

void	insert_env_start(t_env **env)
{
	char	*tmp;

	ft_setenv(env, "CLICOLOR", "1");
	if (!ft_getenv(env, "SHLVL"))
		ft_setenv(env, "SHLVL", "1");
	else
	{
		tmp = ft_itoa(ft_atoi(ft_getenv(env, "SHLVL")) + 1);
		ft_setenv(env, "SHLVL", tmp);
		ft_strdel(&tmp);
	}
}
