/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:25:58 by hlely             #+#    #+#             */
/*   Updated: 2018/03/15 16:11:07 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		launch_and(t_init *init, t_ast *ast, int std_fd[])
{
	int		ret;
	int		status;

	ret = launch_exec(init, ast->left, std_fd);
	reset_fd(std_fd, ast->left, RESETALL);
	status = wait_pipe(&init->pid_list);
	if (status != -1)
		ret = status;
	if (!ret)
	{
		launch_exec(init, ast->right, std_fd);
		reset_fd(std_fd, ast->right, RESETALL);
		wait_pipe(&init->pid_list);
	}
}

void		launch_or(t_init *init, t_ast *ast, int std_fd[])
{
	int		ret;
	int		status;

	ret = launch_exec(init, ast->left, std_fd);
	reset_fd(std_fd, ast->left, RESETALL);
	status = wait_pipe(&init->pid_list);
	if (status != -1)
		ret = status;
	if (ret)
	{
		launch_exec(init, ast->right, std_fd);
		reset_fd(std_fd, ast->right, RESETALL);
		wait_pipe(&init->pid_list);
	}
}
