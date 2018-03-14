/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:24:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/14 11:00:27 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		fork_cmd(t_init *init, t_ast *ast, char *path)
{
	char	**envir;
	int		ret;
	pid_t	father;

	ret = 0;
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
		if (is_builtin(ast->cmd->arg[0]))
			exit(check_builtins(&ast->cmd->arg, ast->cmd, init));
		envir = put_in_tab(&init->new_env);
		execve(path, ast->cmd->arg, envir);
	}
	ft_strdel(&path);
	return (ret);
}

int		exec_cmd(t_ast *ast, t_init *init)
{
	int		ret;

	ret = check_cmd(ast, init);
	return (ret);
}

int		launch_exec(t_init *init, t_ast *ast, int std_fd[])
{
	if (ast)
	{
		if (ast->value == SEMI)
			launch_semi(init, ast, std_fd);
		else if (ast->value == PIPE)
			launch_pipe(init, ast, std_fd);
		else if (ast->value == AND_IF)
			launch_and(init, ast, std_fd);
		else if (ast->value == OR_IF)
			launch_or(init, ast, std_fd);
		else if (ast->value == CMD && ast->cmd && ast->cmd->arg)
			return (exec_cmd(ast, init));
	}
	return (0);
}

int		exec_start(t_init *init)
{
	t_ast	*ast;
	int		std_fd[3];

	ast = init->ast;
	saving_fd(std_fd);
	launch_exec(init, ast, std_fd);
	wait_pipe(&init->pid_list);
	reset_fd(std_fd, NULL, RESETALL);
	return (0);
}
