/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:25:58 by hlely             #+#    #+#             */
/*   Updated: 2018/04/17 10:46:48 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		launch_and(t_init *init, t_ast *ast, int std_fd[], int error)
{
	int status;
	int ret;

	if (ast->parent && ast->parent->left == ast && g_status == 0)
	{
		ret = launch_exec(init, ast, std_fd, error);
		reset_fd(std_fd, ast->cmd);
		saving_fd(std_fd);
		status = wait_pipe(&init->pid_list, ret);
	}
	else if (ast->value != CMD ||
			(ast->parent && ast->parent->right == ast && g_status == 0))
	{
		ret = launch_exec(init, ast, std_fd, error);
		reset_fd(std_fd, ast->cmd);
		wait_pipe(&init->pid_list, ret);
	}

}

void		launch_or(t_init *init, t_ast *ast, int std_fd[], int error)
{
	int status;
	int ret;

	if (ast->parent && ast->parent->left == ast && g_status == 0)
	{
		ret = launch_exec(init, ast, std_fd, error);
		reset_fd(std_fd, ast->cmd);
		saving_fd(std_fd);
		status = wait_pipe(&init->pid_list, ret);
	}
	else if (ast->value != CMD ||
			(ast->parent && ast->parent->right == ast && g_status == 1))
	{
		ret = launch_exec(init, ast, std_fd, error);
		reset_fd(std_fd, ast->cmd);
		wait_pipe(&init->pid_list, ret);
	}

}
