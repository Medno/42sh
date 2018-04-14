/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:43:53 by hlely             #+#    #+#             */
/*   Updated: 2018/04/14 14:16:57 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	close_loop(t_ast *ast)
{
	while (ast->parent->parent && ast->parent->parent->value == PIPE)
	{
		close(ast->parent->parent->pipefd[0]);
		ast = ast->parent;
	}
}

void	close_pipe(t_ast *ast)
{
	if (ast->parent && ast->parent->value == PIPE)
	{
		if (ast->parent->left && ast->cmd == ast->parent->left->cmd)
			close(ast->parent->pipefd[1]);
		else
		{
			if (ast->parent->parent)
				close_loop(ast);
			close(ast->parent->pipefd[0]);
		}
	}
}

void	setup_pipe(t_ast *ast)
{
	if (ast->parent && ast->parent->value == PIPE)
	{
		if (ast->parent->left && ast->cmd == ast->parent->left->cmd)
		{
			if (ast->parent->parent && ast->parent->parent->value == PIPE)
				dup2(ast->parent->parent->pipefd[0], STDIN_FILENO);
			dup2(ast->parent->pipefd[1], STDOUT_FILENO);
			close(ast->parent->pipefd[0]);
		}
		else
		{
			dup2(ast->parent->pipefd[0], STDIN_FILENO);
			close(ast->parent->pipefd[1]);
		}
	}
}

void	launch_pipe(t_init *init, t_ast *ast, int std_fd[], int error)
{
	pipe(ast->pipefd);
	launch_exec(init, ast->left, std_fd, error);
	launch_exec(init, ast->right, std_fd, error);
}

int		wait_pipe(t_pid **pid, t_ast *ast, int sig)
{
	t_pid	*tmp;
	int		status;

	tmp = *pid;
	status = -1;
	while (*pid)
	{
		waitpid((*pid)->pid, &status, 0);
		if (!WIFEXITED(status) && WIFSIGNALED(status))
			signal_error(status, (*pid)->pid);
		*pid = (*pid)->next;
	}
	*pid = tmp;
	del_pid(pid);
	if (!(!WIFEXITED(status) && WIFSIGNALED(status)))
	{
		if (status >= 0 && sig == 0)
			g_status = WEXITSTATUS(status);
		else if (return_builtin(ast))
			g_status = sig;
	}
	return (status);
}
