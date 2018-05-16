/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:17:46 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 11:58:02 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			is_builtin(char *str)
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

int			check_builtins(char ***entry, t_cmd *cmd, t_ast *ast, t_init *init)
{
	if (!redirection(init, cmd))
		return (1);
	if (ft_strequ(**entry, "cd"))
		return (ft_cd(init, entry));
	if (ft_strequ(**entry, "export"))
		return (ft_export(init, entry));
	if (ft_strequ(**entry, "echo"))
		return (ft_echo(&(*entry)[1]));
	if (ft_strequ(**entry, "env"))
		return (ft_env(init, ast, *entry));
	if (ft_strequ(**entry, "setenv"))
		return (ft_setenv_init(init, *entry));
	if (ft_strequ(**entry, "unsetenv"))
		return (ft_biunsetenv(init, entry));
	if (ft_strequ(**entry, "set"))
		return (ft_set(init->loc_env, init->new_env, *entry));
	if (ft_strequ(**entry, "unset"))
		return (ft_unset(&init->loc_env, &init->new_env, *entry));
	if (ft_strequ(**entry, "history"))
		return (ft_history(&init->historic, *entry));
	if (ft_strequ(**entry, "exit"))
		return (ft_exit(init, *entry));
	return (-1);
}

static int	setup_exec(t_init *init, t_ast *ast)
{
	g_oldstatus = g_status;
	g_status = 0;
	ft_set_tmp(init, ast, ast->cmd->arg);
	return (0);
}

int			check_cmd(t_ast *ast, t_init *init)
{
	int		ret;
	char	*path;

	ret = setup_exec(init, ast);
	if (((ast->parent && ast->parent->value != PIPE) || !ast->parent) &&
		(check_local(&ast->cmd->arg, CLEAN) || (is_builtin(ast->cmd->arg[0])))
		&& (ret = check_builtins(&ast->cmd->arg, ast->cmd, ast, init)) >= 0)
	{
		free_list(&init->env_tmp);
		return (ret);
	}
	path = NULL;
	(ast->cmd->arg) ? clean_arg(&ast->cmd->arg) : 0;
	if (!ast->cmd->arg || (ast->cmd->arg && !ast->cmd->arg[0]))
	{
		free_list(&init->env_tmp);
		return (0);
	}
	if (!fork_cmd(init, ast, path))
	{
		free_list(&init->env_tmp);
		return (0);
	}
	free_list(&init->env_tmp);
	return (ret);
}
