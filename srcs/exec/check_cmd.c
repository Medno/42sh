/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:17:46 by hlely             #+#    #+#             */
/*   Updated: 2018/03/14 10:51:24 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_builtin g_builtin[] =
{
	{"cd"		, &ft_cd},
	{"echo"		, &ft_echo},
	{"env"		, &ft_env},
	{"setenv"	, &ft_bisetenv},
	{"unsetenv"	, &ft_biunsetenv},
	{"export"	, &ft_export},
	{"history"	, &ft_history},
	{"set"		, &ft_set},
	{"unset"	, &ft_unset},
	{"exit"		, &ft_exit},
	{NULL		, NULL},
};

int		is_builtin(char *str)
{
	int i;

	i = 0;
	while (g_builtin[i].value)
	{
		if (ft_strequ(g_builtin[i].value, str))
			return (1);
		i++;
	}
	return (0);
}

int		check_builtins(char ***entry, t_cmd *cmd, t_init *init)
{
	int i;

	if (!redirection(cmd))
		return (1);
	if (check_local(entry))
		return (ft_set_local(&init->loc_env, &init->new_env, *entry));
	i = 0;
	while (g_builtin[i].value)
	{
		if (ft_strequ(g_builtin[i].value, **entry))
			return (g_builtin[i].f(init, entry));
		i++;
	}
	return (-1);
}

int		check_cmd(t_ast *ast, t_init *init)
{
	int		ret;
	char	*path;

	if (((ast->parent && ast->parent->value != PIPE) || !ast->parent)  &&
			is_builtin(ast->cmd->arg[0]) &&
			(ret = check_builtins(&ast->cmd->arg, ast->cmd, init)) >= 0)
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
