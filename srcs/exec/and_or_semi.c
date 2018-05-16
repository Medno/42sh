/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:25:58 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 12:10:50 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	exec_left(t_init *init, t_ast *ast, int std_fd[], int error)
{
	int		ret;

	ret = launch_exec(init, ast, std_fd, error);
	reset_fd(init, std_fd, ast->cmd);
	saving_fd(std_fd);
	wait_pipe(&init->pid_list, ret);
}

static void	exec_right(t_init *init, t_ast *ast, int std_fd[], int error)
{
	launch_exec(init, ast, std_fd, error);
	reset_fd(init, std_fd, ast->cmd);
}

void		launch_and(t_init *init, t_ast *ast, int std_fd[], int error)
{
	if (ast->parent && ast->parent->left == ast &&
			(!ast->parent->parent ||
			(ast->parent->parent->value != AND_IF &&
			ast->parent->parent->value != OR_IF)))
		exec_left(init, ast, std_fd, error);
	else if (ast->parent && ast->parent->left == ast &&
			ast->parent->parent &&
			ast->parent->parent->value == OR_IF && g_status == 1)
		exec_left(init, ast, std_fd, error);
	else if (ast->parent && ast->parent->left == ast &&
			ast->parent->parent &&
			ast->parent->parent->value == AND_IF && g_status == 0)
		exec_left(init, ast, std_fd, error);
	else if (ast->value != CMD ||
			(ast->parent && ast->parent->right == ast && g_status == 0))
		exec_right(init, ast, std_fd, error);
}

void		launch_or(t_init *init, t_ast *ast, int std_fd[], int error)
{
	if (ast->parent && ast->parent->left == ast &&
			(!ast->parent->parent ||
			(ast->parent->parent->value == AND_IF && g_status == 0) ||
			(ast->parent->parent->value == OR_IF && g_status == 1) ||
			(ast->parent->parent->value != OR_IF &&
			ast->parent->parent->value != AND_IF)))
		exec_left(init, ast, std_fd, error);
	else if (ast->value != CMD ||
			(ast->parent && ast->parent->right == ast && g_status == 1))
		exec_right(init, ast, std_fd, error);
}
