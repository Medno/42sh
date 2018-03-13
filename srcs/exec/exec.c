/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:24:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/13 15:23:41 by hlely            ###   ########.fr       */
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
		envir = put_in_tab(&init->new_env);
		execve(path, ast->cmd->arg, envir);
	}
	ft_strdel(&path);
	return (ret);
}

int		exec_cmd(t_ast *ast, t_init *init)
{
	int		std_fd[3];
	int		ret;

	saving_fd(std_fd);
	if (!redirection(ast->cmd))
		return (reset_fd(std_fd, ast->cmd->redir));
	ret = check_cmd(ast, init);
	reset_fd(std_fd, ast->cmd->redir);
	return (ret);
}

int		launch_exec(t_init *init, t_ast *ast)
{
	int		ret;

	if (ast)
	{
		if (ast->value == SEMI)
		{
			launch_exec(init, ast->left);
			wait_pipe(&init->pid_list);
			launch_exec(init, ast->right);
			wait_pipe(&init->pid_list);
		}
		else if (ast->value == PIPE)
			launch_pipe(init, ast);
		else if (ast->value == AND_IF)
		{
			if (!(ret = launch_exec(init, ast->left)))
				launch_exec(init, ast->right);
		}
		else if (ast->value == OR_IF)
		{
			if ((ret = launch_exec(init, ast->left)))
				launch_exec(init, ast->right);
		}
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
	launch_exec(init, ast);
	wait_pipe(&init->pid_list);
	reset_fd(std_fd, NULL);
	return (0);
}
