/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:04:49 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 11:38:55 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	create_loc(t_init *init)
{
	if (!ft_getenv(&init->new_env, "PATH"))
		ft_setenv(&init->loc_env, "PATH", "/bin:/usr/bin");
}

static int	get_pwd(t_init *init)
{
	init->pwd = getcwd(NULL, PATH_MAX);
	if (!init->pwd)
	{
		ft_printf_fd(2, "shell-init: error retrieving current directory\n");
		return (0);
	}
	return (1);
}

int			init_all(char **env, t_init *init)
{
	struct termios	current;

	tcgetattr(STDIN_FILENO, &current);
	init->str = NULL;
	init->stop = 0;
	init->dollar = 0;
	init->lex = NULL;
	init->ast = NULL;
	init->loc_env = NULL;
	init->env_tmp = NULL;
	init->pid_list = NULL;
	init->pipe = NULL;
	if (!get_pwd(init))
		return (0);
	init->new_env = (env) ? create_env(env) : NULL;
	insert_env_start(&init->new_env);
	init->historic = new_hist();
	init->current = current;
	create_loc(init);
	return (1);
}
