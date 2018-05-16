/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:24:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/16 12:10:04 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	exec_cmd(t_init *init, t_ast *ast, char *path)
{
	int		ret;
	char	**envir;

	if (is_builtin(ast->cmd->arg[0]) || check_local(&ast->cmd->arg, CLEAN))
		exit(check_builtins(&ast->cmd->arg, ast->cmd, ast, init));
	if (!(ret = check_path(ast->cmd->arg, init, &path, PRINT)))
	{
		envir = put_in_tab((init->env_tmp) ? &init->env_tmp : &init->new_env);
		execve(path, ast->cmd->arg, envir);
		error_execve();
	}
	else
		exit_error(ret, ast->cmd->arg[0]);
}

int		fork_cmd(t_init *init, t_ast *ast, char *path)
{
	pid_t	father;

	father = fork();
	if (father == -1)
		return (clean_pipe(init));
	if (father > 0)
	{
		pid_addlast(&init->pid_list, father);
		signal(SIGINT, (void (*)(int))sig_write_nl);
		signal(SIGQUIT, (void (*)(int))sig_write_nl);
		close_pipe(ast);
	}
	if (!father)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_pipe(ast);
		if (!redirection(init, ast->cmd))
			exit(EXIT_FAILURE);
		exec_cmd(init, ast, path);
	}
	ft_strdel(&path);
	return (1);
}

int		launch_exec(t_init *init, t_ast *ast, int std_fd[], int error)
{
	if (ast)
	{
		ast->cmd = ast->cmd ? begin_expansion(init, ast->cmd) : ast->cmd;
		if (ast->value == PIPE)
			launch_pipe(init, ast, std_fd, error);
		else if (ast->value == AND_IF)
		{
			launch_and(init, ast->left, std_fd, error);
			launch_and(init, ast->right, std_fd, error);
		}
		else if (ast->value == OR_IF)
		{
			launch_or(init, ast->left, std_fd, error);
			launch_or(init, ast->right, std_fd, error);
		}
		else if (ast->value == CMD && ast->cmd && ast->cmd->arg)
			return (check_cmd(ast, init));
		else if (ast->value == CMD && ast->cmd && !ast->cmd->arg)
			return (only_redir(init, ast));
	}
	return (0);
}

int		exec_start(t_ast *ast, t_init *init)
{
	int		std_fd[3];
	int		ret;
	int		sig;
	int		error;

	error = 0;
	saving_fd(std_fd);
	sig = launch_exec(init, ast, std_fd, error);
	ret = wait_pipe(&init->pid_list, sig);
	del_pipe(&init->pipe);
	reset_fd(init, std_fd, ast->cmd);
	return (ret);
}
