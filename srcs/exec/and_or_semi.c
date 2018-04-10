/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:25:58 by hlely             #+#    #+#             */
/*   Updated: 2018/04/10 17:10:01 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		launch_and(t_init *init, t_ast *ast, int std_fd[], int error)
{
	int		ret;
	int		status;

	ret = launch_exec(init, ast->left, std_fd, error);
	reset_fd(std_fd);
	status = wait_pipe(&init->pid_list, ret);
	if (status != -1)
		ret = status;
	error = ret;
	if (!ret || (ast->right && ast->right->value == OR_IF))
	{
		ret = launch_exec(init, ast->right, std_fd, error);
		reset_fd(std_fd);
		wait_pipe(&init->pid_list, ret);
	}
}

void		launch_or(t_init *init, t_ast *ast, int std_fd[], int error)
{
	int		ret;
	int		status;

	if (!error)
	{
		ret = launch_exec(init, ast->left, std_fd, error);
		reset_fd(std_fd);
		status = wait_pipe(&init->pid_list, ret);
		if (status != -1)
			ret = status;
		if (ret)
		{
			ret = launch_exec(init, ast->right, std_fd, error);
			reset_fd(std_fd);
			wait_pipe(&init->pid_list, ret);
		}
	}
	else
	{
		ret = launch_exec(init, ast->right, std_fd, error);
		reset_fd(std_fd);
		wait_pipe(&init->pid_list, ret);
	}
}
