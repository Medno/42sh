/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 10:38:00 by hlely             #+#    #+#             */
/*   Updated: 2018/04/13 08:18:58 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	saving_fd(int fd[])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
}

int		reset_fd(int fd[], t_cmd *cmd)
{
	t_redir	*tmp;

	if (cmd && cmd->redir)
	{
		tmp = cmd->redir;
		while (tmp)
		{
			close(tmp->fd_out);
			tmp = tmp->next;
		}
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	return (2);
}
