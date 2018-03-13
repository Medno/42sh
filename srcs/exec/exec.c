/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:24:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/13 14:54:26 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_builtins(char ***entry, t_init *init)
{
	if (check_local(entry))
		return (ft_set_local(&init->loc_env, &init->new_env, *entry));
	else if (ft_strequ("cd", **entry))
		return (ft_cd(&init->new_env, *entry, ft_tablen(*entry)));
	else if (ft_strequ("echo", **entry))
		return (ft_echo(&(*entry)[1]));
	else if (ft_strequ("env", **entry)) 
		return (ft_env(init->new_env, *entry));
	else if (ft_strequ("setenv", **entry)) 
		return (ft_setenv(&init->new_env, (*entry)[1], (*entry)[2]));
	else if (ft_strequ("unsetenv", **entry))
		return (ft_unsetenv(&init->new_env, (*entry)[1]));
	else if (ft_strequ("export", **entry)) 
		return (ft_export(&init->loc_env, &init->new_env, *entry));
	else if (ft_strequ("history", **entry))
		return (ft_history(&init->historic, *entry, ft_tablen(*entry)));
	else if (ft_strequ("set", **entry))
		return (ft_set(init->loc_env, init->new_env, *entry));
	else if (ft_strequ("unset", **entry))
		return (ft_unset(&init->loc_env, &init->new_env, *entry));
	else if (ft_strequ("exit", **entry))
		ft_exit(init);
	return (-1);
}

void	close_loop(t_ast *ast)
{
	while (ast->parent->parent && ast->parent->parent->value == PIPE)
	{
		close(ast->parent->parent->pipefd[0]);
		ast = ast->parent;
	}
}

void	close_pipe(t_ast *ast)
{
	if (ast->parent && ast->parent->value == PIPE)
	{
		if (ast->parent->left && ast->cmd == ast->parent->left->cmd)
		{
			close(ast->parent->pipefd[1]);
		}
		else
		{
			if (ast->parent->parent)
				close_loop(ast);
			close(ast->parent->pipefd[0]);
		}
	}
}

void	setup_pipe(t_ast *ast)
{
	if (ast->parent && ast->parent->value == PIPE)
	{
		if (ast->parent->left && ast->cmd == ast->parent->left->cmd)
		{
			if (ast->parent->parent && ast->parent->parent->value == PIPE)
			{
				dup2(ast->parent->parent->pipefd[0], STDIN_FILENO);
			}
			dup2(ast->parent->pipefd[1], STDOUT_FILENO);
			close(ast->parent->pipefd[0]);
		}
		else
		{
			dup2(ast->parent->pipefd[0], STDIN_FILENO);
			close(ast->parent->pipefd[1]);
		}
	}
}

int		fork_cmd(t_init *init, t_ast *ast, char *path)
{
	char	**envir;
	int		ret;
	pid_t	father;

	ret = 0;
	father = fork();
	if (father > 0)
	{
		pid_addlast(&init->pid_list, father);
		signal(SIGINT, (void (*)(int))sig_write_nl);
		close_pipe(ast);
	}
	if (!father)
	{
		signal(SIGINT, SIG_DFL);
		setup_pipe(ast);
		envir = put_in_tab(&init->new_env);
		execve(path, ast->cmd->arg, envir);
	}
	ft_strdel(&path);
	return (ret);
}

int		check_cmd(t_ast *ast, t_init *init)
{
	int		ret;
	char	*path;

	if ((ret = check_builtins(&ast->cmd->arg, init)) >= 0)
		return (ret);
	else
	{
		if (!(ret = check_path(ast->cmd->arg[0], &init->new_env, &path)))
			return (fork_cmd(init, ast, path));
		else
		{
			if (ret == 1)
				ft_printf_fd(2, "42sh: %s: command not found\n",
						ast->cmd->arg[0]);
			return (1);
		}
		return (0);
	}
}

int		exec_cmd(t_ast *ast, t_init *init)
{
	int		std_fd[3];
	int		ret;

	saving_fd(std_fd);
	if (!redirection(ast->cmd))
		return (reset_fd(std_fd, ast->cmd->redir));
	ret = check_cmd(ast, init);
	reset_fd(std_fd, ast->cmd->redir);
	return (ret);
}

void	print_pid(t_pid *pid)
{
	if (!pid)
		ft_printf_fd(STDERR_FILENO, "Empty\n");
	else
	{
		while (pid)
		{
			ft_printf_fd(STDERR_FILENO, "PID=%d\n", pid->pid);
			pid = pid->next;
		}
	}
}

int		launch_exec(t_init *init, t_ast *ast)
{
	int		ret;

	if (ast)
	{
		if (ast->value == SEMI)
		{
			launch_exec(init, ast->left);
			wait_pipe(&init->pid_list);
			launch_exec(init, ast->right);
			wait_pipe(&init->pid_list);
		}
		else if (ast->value == PIPE)
			/* launch_pipe(init, ast); */
			launch_pipe_wofork(init, ast);
		else if (ast->value == AND_IF)
		{
			if (!(ret = launch_exec(init, ast->left)))
				launch_exec(init, ast->right);
		}
		else if (ast->value == OR_IF)
		{
			if ((ret = launch_exec(init, ast->left)))
				launch_exec(init, ast->right);
		}
		else if (ast->value == CMD && ast->cmd && ast->cmd->arg)
			return (exec_cmd(ast, init));
	}
	return (0);
}

int		exec_start(t_init *init)
{
	t_ast	*ast;
	int		std_fd[3];

	ast = init->ast;
	saving_fd(std_fd);
	launch_exec(init, ast);
	wait_pipe(&init->pid_list);
	reset_fd(std_fd, NULL);
	return (0);
}
