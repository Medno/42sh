/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:25:58 by hlely             #+#    #+#             */
/*   Updated: 2018/03/15 14:03:37 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		launch_and(t_init *init, t_ast *ast, int std_fd[])
{
	int		ret;
	int		status;

	ret = launch_exec(init, ast->left, std_fd);
	status = wait_pipe(&init->pid_list);
	reset_fd(std_fd, ast->left, RESETALL);
	if (status != -1)
		ret = status;
	if (!ret)
	{
		launch_exec(init, ast->right, std_fd);
		wait_pipe(&init->pid_list);
		reset_fd(std_fd, ast->right, RESETALL);
	}
}

void		launch_or(t_init *init, t_ast *ast, int std_fd[])
{
	int		ret;
	int		status;

	ret = launch_exec(init, ast->left, std_fd);
	status = wait_pipe(&init->pid_list);
	reset_fd(std_fd, ast->left, RESETALL);
	if (status != -1)
		ret = status;
	if (ret)
	{
		launch_exec(init, ast->right, std_fd);
		wait_pipe(&init->pid_list);
		reset_fd(std_fd, ast->right, RESETALL);
	}
}

void		launch_semi(t_init *init, t_ast *ast, int std_fd[])
{
	launch_exec(init, ast->left, std_fd);
	wait_pipe(&init->pid_list);
	reset_fd(std_fd, ast->left, RESETALL);
	launch_exec(init, ast->right, std_fd);
	wait_pipe(&init->pid_list);
	reset_fd(std_fd, ast->right, RESETALL);
}
