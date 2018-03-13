/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:17:46 by hlely             #+#    #+#             */
/*   Updated: 2018/03/13 15:17:48 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_builtins(char ***entry, t_init *init)
{
	if (check_local(entry))
		return (ft_set_local(&init->loc_env, &init->new_env, *entry));
	else if (ft_strequ("cd", **entry))
		return (ft_cd(&init->new_env, *entry, ft_tablen(*entry)));
	else if (ft_strequ("echo", **entry))
		return (ft_echo(&(*entry)[1]));
	else if (ft_strequ("env", **entry))
		return (ft_env(init->new_env, *entry));
	else if (ft_strequ("setenv", **entry))
		return (ft_setenv(&init->new_env, (*entry)[1], (*entry)[2]));
	else if (ft_strequ("unsetenv", **entry))
		return (ft_unsetenv(&init->new_env, (*entry)[1]));
	else if (ft_strequ("export", **entry))
		return (ft_export(&init->loc_env, &init->new_env, *entry));
	else if (ft_strequ("history", **entry))
		return (ft_history(&init->historic, *entry, ft_tablen(*entry)));
	else if (ft_strequ("set", **entry))
		return (ft_set(init->loc_env, init->new_env, *entry));
	else if (ft_strequ("unset", **entry))
		return (ft_unset(&init->loc_env, &init->new_env, *entry));
	else if (ft_strequ("exit", **entry))
		ft_exit(init);
	return (-1);
}

int		check_cmd(t_ast *ast, t_init *init)
{
	int		ret;
	char	*path;

	if ((ret = check_builtins(&ast->cmd->arg, init)) >= 0)
		return (ret);
	else
	{
		if (!(ret = check_path(ast->cmd->arg[0], &init->new_env, &path)))
			return (fork_cmd(init, ast, path));
		else
		{
			if (ret == 1)
				ft_printf_fd(2, "42sh: %s: command not found\n",
						ast->cmd->arg[0]);
			return (1);
		}
		return (0);
	}
}
