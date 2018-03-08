/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:24:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/08 10:14:49 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_builtins(char **entry, t_init *init)
{
	if (ft_strequ("cd", *entry))
		return (ft_cd(&init->new_env, entry, ft_tablen(entry)));
	else if (ft_strequ("echo", *entry))
		return (ft_echo(&entry[1]));
	else if (ft_strequ("env", *entry)) 
		return (ft_env(init->new_env, entry));
	else if (ft_strequ("setenv", *entry)) 
		return (ft_setenv(&init->new_env, entry[1], entry[2]));
	else if (ft_strequ("unsetenv", *entry))
		return (ft_unsetenv(&init->new_env, entry[1]));
	else if (ft_strequ("export", *entry)) 
		return 0;
	else if (ft_strequ("history", *entry))
		return (ft_history(&init->historic, entry, ft_tablen(entry)));
	else if (ft_strequ("exit", *entry))
		ft_exit(init);
	return (-1);
}

int		fork_cmd(t_env **env, t_cmd *cmd, char *path)
{
	char	**envir;
	int		ret;
	pid_t	father;

	ret = 0;
	if ((father = fork()) > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&ret);
	}
	if (!father)
	{
		signal(SIGINT, SIG_DFL);
		envir = put_in_tab(env);
		execve(path, cmd->arg, envir);
		ft_freetab(envir);
		ft_strdel(&path);
	}
	return (ret);
}

int		check_cmd(t_cmd *cmd, t_init *init)
{
	int		ret;
	char	*path;

	if ((ret = check_builtins(cmd->arg, init)) >= 0)
		return (ret);
	else
	{
		if (!(ret = check_path(cmd->arg[0], &init->new_env, &path)))
			return (fork_cmd(&init->new_env, cmd, path));
		else
		{
			if (ret == 1)
				ft_printf_fd(2, "42sh: %s: command not found\n", cmd->arg[0]);
			return (1);
		}
		return (0);
	}
}

int		check_sep(int ret, char *s)
{
	if (ft_strequ(s, "&&"))
	{
		if (!ret)
			return (0);
		else
			return (1);
	}
	else if (ft_strequ(s, "||"))
	{
		if (!ret)
			return (1);
		else
			return (0);
	}
	return (0);
}

int		exec_start(t_init *init)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;
	int		std_fd[3];
	int		ret;

	tmp2 = init->cmd;
	while (tmp2)
	{
		tmp = tmp2;
		while (tmp)
		{
			saving_fd(std_fd);
			if (!redirection(tmp))
				return (reset_fd(std_fd, tmp->redir));
			ret = check_cmd(tmp, init);
			reset_fd(std_fd, tmp->redir);
			if (check_sep(ret, tmp->separ))
				tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
		tmp2 = tmp2->next_semi;
	}
	return (0);
}
