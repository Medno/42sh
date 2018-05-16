/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 14:06:32 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 11:57:18 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_all_path(char **arg, t_init *init, char **s_fin, int print)
{
	if (!arg || !*arg)
		return (1);
	if (ft_strchr(*arg, '/'))
		return (check_slash(init, *arg, s_fin, print));
	else if (ft_getenv(&init->new_env, "PATH") ||
			ft_getenv(&init->loc_env, "PATH"))
		return (check_bin(*arg, init, s_fin, print));
	else
		return (check_error(-1, *arg, print));
}

static void	exec_env_cmd(t_init *init, t_ast *ast, char *path)
{
	int		ret;
	char	**envir;

	if (!(ret = check_all_path(ast->cmd->arg, init, &path, PRINT)))
	{
		envir = put_in_tab(&init->new_env);
		execve(path, ast->cmd->arg, envir);
		error_execve();
	}
	else
		exit_error(ret, ast->cmd->arg[0]);
}

void		fork_env_cmd(t_init *init, t_ast *ast, char *path)
{
	pid_t	father;

	if (ast->cmd->arg[0])
	{
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
			if (!redirection(init, ast->cmd))
				exit(EXIT_FAILURE);
			exec_env_cmd(init, ast, path);
		}
	}
	ft_strdel(&path);
}
