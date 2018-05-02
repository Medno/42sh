/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:08:45 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/02 15:19:42 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	print_env(t_env **env)
{
	ft_print_env(*env, 0);
	free_list(env);
	return (0);
}

int			fill_env(t_env **env, char **arg)
{
	int		i;
	char	*name;
	char	*value;

	i = inc_opt(arg);
	while (arg[i] && ft_strchr(arg[i], '='))
	{
		name = ft_strsub(arg[i], 0, equ_index(arg[i], '='));
		value = ft_strchr(arg[i], '=') + 1;
		if (!name || !*name)
		{
			free_list(env);
			ft_strdel(&name);
			return (usage_env());
		}
		ft_setenv(env, name, value);
		ft_strdel(&name);
		i++;
	}
	if (!arg[i])
		return (print_env(env));
	return (0);
}

static int	ft_env_return(t_env *new, t_ast *ast, char **arg)
{
	t_init	initmp;
	t_ast	*astmp;
	int		ret;

	ret = fill_env(&new, arg);
	if (!ret && (new || (!new && arg[1] && arg[2])))
	{
		init_all(NULL, &initmp);
		astmp = init_ast();
		free_list(&initmp.new_env);
		initmp.new_env = new;
		if (!ft_getenv(&new, "PATH"))
			ft_setenv(&initmp.loc_env, "PATH", "/bin:/usr/bin");
		astmp->cmd = init_cmd();
		astmp->value = CMD;
		astmp->cmd->arg = shift_arg(ast->cmd->arg);
		fork_env_cmd(&initmp, astmp, NULL);
		ret = wait_pipe(&initmp.pid_list, 127);
		clean_ast(&astmp);
		clean_init(&initmp);
		ft_freetab(ast->cmd->arg);
		ast->cmd->arg = NULL;
	}
	return (ret);
}

static int	set_bits(int c, int flag)
{
	if (c == 'i')
		flag |= 1;
	return (flag);
}

int			ft_env(t_init *init, t_ast *ast, char **arg)
{
	t_env	*new;
	int		flags;
	int		c;

	c = 0;
	flags = 0;
	new = NULL;
	if (!arg[1])
		return (ft_print_env(init->env_tmp, 0));
	reset_ft_opt();
	while ((c = ft_getopt(ft_tablen(arg), arg, "i")) != -1)
	{
		if (c == 'i')
			flags = set_bits(c, flags);
		else if (c == '?')
			return (usage_env());
	}
	if (!flags)
		new = cpyenv(init->new_env);
	else if (flags & 1)
		new = NULL;
	return (ft_env_return(new, ast, arg));
}
