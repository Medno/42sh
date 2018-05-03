/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 10:38:00 by hlely             #+#    #+#             */
/*   Updated: 2018/05/03 13:08:07 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	saving_fd(int fd[])
{
	fd[0] = 10;
	fd[1] = 11;
	fd[2] = 12;
	fd[0] = dup2(STDIN_FILENO, fd[0]);
	fd[1] = dup2(STDOUT_FILENO, fd[1]);
	fd[2] = dup2(STDERR_FILENO, fd[2]);
}

void	close_fd(t_cmd *cmd)
{
	t_redir	*tmp;

	if (cmd && cmd->redir)
	{
		tmp = cmd->redir;
		while (tmp)
		{
			if (tmp->fd_out > 2)
				close(tmp->fd_out);
			tmp = tmp->next;
		}
	}
}

int		reset_fd(int fd[], t_cmd *cmd)
{
	close_fd(cmd);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	return (2);
}
