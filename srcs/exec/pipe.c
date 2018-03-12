/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:43:53 by hlely             #+#    #+#             */
/*   Updated: 2018/03/12 17:31:25 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	launch_pipe(t_init *init, t_ast *ast)
{
	pid_t	father;
	int		pipefd[2];

	pipe(pipefd);
	father = fork();
	if (father)
	{
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
