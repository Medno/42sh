/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:43:53 by hlely             #+#    #+#             */
/*   Updated: 2018/03/13 15:23:49 by hlely            ###   ########.fr       */
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

void	launch_pipe(t_init *init, t_ast *ast)
{
	pipe(ast->pipefd);
	launch_exec(init, ast->left);
	launch_exec(init, ast->right);
}

void	wait_pipe(t_pid **pid)
{
	t_pid	*tmp;

	tmp = *pid;
	while (*pid)
	{
		waitpid((*pid)->pid, NULL, 0);
		*pid = (*pid)->next;
	}
	*pid = tmp;
	del_pid(pid);
}
