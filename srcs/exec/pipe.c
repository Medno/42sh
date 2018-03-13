/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:43:53 by hlely             #+#    #+#             */
/*   Updated: 2018/03/13 14:15:54 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	launch_pipe_wofork(t_init *init, t_ast *ast)
{
	pipe(ast->pipefd);
	launch_exec(init, ast->left);
	/* dup2(ast->right->pipefd[0], ast->pipefd[1]); */
	launch_exec(init, ast->right);
}

void	launch_pipe(t_init *init, t_ast *ast)
{
	pid_t	father;
	int		pipefd[2];

	pipe(pipefd);
	father = fork();
	if (father)
	{
		pid_addlast(&init->pid_list, father);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		launch_exec(init, ast->right);
		close(pipefd[0]);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		launch_exec(init, ast->left);
		close(pipefd[1]);
		exit(0);
	}
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
