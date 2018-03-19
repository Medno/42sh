/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:24:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/19 11:42:21 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	exec_cmd(t_init *init, t_ast *ast, char *path)
{
	int		ret;
	char	**envir;

	if (is_builtin(ast->cmd->arg[0]) || check_local(&ast->cmd->arg, CLEAN))
		exit(check_builtins(&ast->cmd->arg, ast->cmd, ast, init));
	if (!(ret = check_path(ast->cmd->arg, init, &path, PRINT)))
	{
		envir = put_in_tab(&init->new_env);
		execve(path, ast->cmd->arg, envir);
		error_execve();
	}
	else
		exit_error(ret, ast->cmd->arg[0]);
}

void	fork_cmd(t_init *init, t_ast *ast, char *path)
{
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		pid_addlast(&init->pid_list, father);
		signal(SIGINT, (void (*)(int))sig_write_nl);
		close_pipe(ast);
	}
	if (!father)
	{
		signal(SIGINT, SIG_DFL);
		setup_pipe(ast);
		if (!redirection(ast->cmd))
			exit(EXIT_FAILURE);
		exec_cmd(init, ast, path);
	}
	ft_strdel(&path);
}

int		launch_exec(t_init *init, t_ast *ast, int std_fd[])
{
	if (ast)
	{
		if (ast->value == PIPE)
			launch_pipe(init, ast, std_fd);
		else if (ast->value == AND_IF)
			launch_and(init, ast, std_fd);
		else if (ast->value == OR_IF)
			launch_or(init, ast, std_fd);
		else if (ast->value == CMD && ast->cmd && ast->cmd->arg)
			return (check_cmd(ast, init));
	}
	return (0);
}

int		exec_start(t_ast *ast, t_init *init)
{
	int		std_fd[3];

	saving_fd(std_fd);
	launch_exec(init, ast, std_fd);
	wait_pipe(&init->pid_list);
	reset_fd(std_fd);
	return (0);
}
