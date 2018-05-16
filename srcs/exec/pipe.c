/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:43:53 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 12:12:11 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	close_loop(t_ast *ast)
{
	while (ast->parent->parent && ast->parent->parent->value == PIPE)
	{
		close(ast->parent->parent->pipefd[0]);
		ast = ast->parent;
	}
}

void		close_pipe(t_ast *ast)
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

void		setup_pipe(t_ast *ast)
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

void		launch_pipe(t_init *init, t_ast *ast, int std_fd[], int error)
{
	int		pipefd[2];

	ast->pipefd[0] = get_newfd(&init->pipe);
	ast->pipefd[1] = get_newfd(&init->pipe);
	pipe(pipefd);
	ast->pipefd[0] = dup2(pipefd[0], ast->pipefd[0]);
	ast->pipefd[1] = dup2(pipefd[1], ast->pipefd[1]);
	close(pipefd[0]);
	close(pipefd[1]);
	launch_exec(init, ast->left, std_fd, error);
	close_fd(init, ast->left->cmd);
	launch_exec(init, ast->right, std_fd, error);
	close_fd(init, ast->right->cmd);
}

int			wait_pipe(t_pid **pid, int sig)
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
		if (status == -1)
			g_status = sig;
		else
		{
			g_status = WEXITSTATUS(status);
			status = WEXITSTATUS(status);
		}
	}
	return (status);
}
