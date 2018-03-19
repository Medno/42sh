/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:17:46 by hlely             #+#    #+#             */
/*   Updated: 2018/03/19 10:49:36 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* t_builtin g_builtin[] = */
/* { */
/* 	{"cd"		, &ft_cd}, */
/* 	{"echo"		, &ft_echo}, */
/* 	{"env"		, &ft_env}, */
/* 	{"setenv"	, &ft_bisetenv}, */
/* 	{"unsetenv"	, &ft_biunsetenv}, */
/* 	{"export"	, &ft_export}, */
/* 	{"history"	, &ft_history}, */
/* 	{"set"		, &ft_set}, */
/* 	{"unset"	, &ft_unset}, */
/* 	{"exit"		, &ft_exit}, */
/* 	{NULL		, NULL}, */
/* }; */

int		is_builtin(char *str)
{
	if (ft_strequ(str, "cd"))
		return (1);
	if (ft_strequ(str, "export"))
		return (1);
	if (ft_strequ(str, "echo"))
		return (1);
	if (ft_strequ(str, "env"))
		return (1);
	if (ft_strequ(str, "setenv"))
		return (1);
	if (ft_strequ(str, "unsetenv"))
		return (1);
	if (ft_strequ(str, "export"))
		return (1);
	if (ft_strequ(str, "set"))
		return (1);
	if (ft_strequ(str, "unset"))
		return (1);
	if (ft_strequ(str, "exit"))
		return (1);
	if (ft_strequ(str, "history"))
		return (1);
	return (0);
}

int		check_builtins(char ***entry, t_cmd *cmd, t_ast *ast, t_init *init)
{
	if (!redirection(cmd))
		return (1);
	if (check_local(entry, CLEAN))
		return (ft_set_local(&init->loc_env, &init->new_env, *entry));
	if (ft_strequ(**entry, "cd"))
		return (ft_cd(init, entry));
	if (ft_strequ(**entry, "export"))
		return (ft_export(init, entry));
	if (ft_strequ(**entry, "echo"))
		return (ft_echo(&(*entry)[1]));
	if (ft_strequ(**entry, "env"))
		return (ft_env(init, ast, *entry));
	if (ft_strequ(**entry, "setenv") && (*entry)[1] && (*entry)[2])
		return (ft_setenv(&init->new_env, (*entry)[1], (*entry)[2]));
	if (ft_strequ(**entry, "unsetenv"))
		return (ft_unsetenv(&init->new_env, (*entry)[1]));
	if (ft_strequ(**entry, "set"))
		return (ft_set(init->loc_env, init->new_env, *entry));
	if (ft_strequ(**entry, "unset"))
		return (ft_unset(&init->loc_env, &init->new_env, *entry));
	if (ft_strequ(**entry, "history"))
		return (ft_history(&init->historic, *entry));
	if (ft_strequ(**entry, "exit"))
		ft_exit(init, entry);
	return (-1);
}

int		check_cmd(t_ast *ast, t_init *init)
{
	int		ret;
	char	*path;

	if (((ast->parent && ast->parent->value != PIPE) || !ast->parent) &&
			(is_builtin(ast->cmd->arg[0]) ||
			check_local(&ast->cmd->arg, CLEAN))
			&& (ret = check_builtins(&ast->cmd->arg, ast->cmd, ast, init)) >= 0)
		return (ret);
	else
	{
		path = NULL;
		if (!ast->cmd->arg)
			return (1);
		ret = check_path(ast->cmd->arg, &init->new_env, &path, NOPRINT);
		fork_cmd(init, ast, path);
		return (ret);
	}
}
