/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 10:38:00 by hlely             #+#    #+#             */
/*   Updated: 2018/03/14 09:35:47 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	saving_fd(int fd[])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
}

int		reset_fd(int fd[], t_ast *ast, int flag)
{
	if (flag == RESETALL)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[2], STDERR_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
	}
	(void)ast;
	/* if (ast && ast->cmd && ast->cmd->redir) */
	/* 	close(ast->cmd->redir->fd_out); */
	return (2);
}
