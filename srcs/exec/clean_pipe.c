/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:41:32 by hlely             #+#    #+#             */
/*   Updated: 2018/05/05 11:56:22 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	close_pipe_err(t_ast *ast)
{
	if (ast)
	{
		close(ast->pipefd[0]);
		close(ast->pipefd[1]);
		if (ast->left)
			close_pipe_err(ast->left);
		if (ast->right)
			close_pipe_err(ast->right);
	}
}

int			clean_pipe(t_init *init)
{
	t_pid	*tmp;

	ft_printf_fd(STDERR_FILENO,
			"42sh: fork: Resource temporarily unavailable\n");
	tmp = init->pid_list;
	close_pipe_err(init->ast);
	while (tmp)
	{
		kill(tmp->pid, SIGINT);
		tmp = tmp->next;
	}
	return (0);
}
