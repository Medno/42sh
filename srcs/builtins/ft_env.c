/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:08:45 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/17 15:33:00 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_env		*fill_env(t_env *env, char **arg)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (ft_strequ(arg[i], "-i") || ft_strequ(arg[i], "-"))
		i++;
	while (arg[i] && ft_strchr(arg[i], '='))
	{
		name = ft_strsub(arg[i], 0, equ_index(arg[i], '='));
		value = ft_strchr(arg[i], '=') + 1;
		ft_setenv(&env, name, value);
		ft_strdel(&name);
		i++;
	}
	if (!arg[i])
	{
		ft_print_env(env);
		free_list(&env);
		return (NULL);
	}
	return (env);
}

static char	**cpytab(char **dest, char **src)
{
	int		i;

	i = 0;
	dest = (char**)ft_memalloc(sizeof(char*) * (ft_tablen(src) + 1));
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static t_env	*cpyenv(t_env *env)
{
	t_env	*new;
	t_env	*one;
	t_env	*tmp;

	new = NULL;
	while (env)
	{
		one = (t_env*)ft_memalloc(sizeof(t_env));
		one->name = ft_strdup(env->name);
		one->content = ft_strdup(env->content);
		if (!new)
			new = one;
		else
		{
			tmp = new;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = one;
		}
		env = env->next;
	}
	return (new);
}

static char	**shift_arg(char **arg)
{
	int		i;
	char	**newarg;

	i = 1;
	newarg = NULL;
	if (arg[i] && ft_strequ(arg[i], "-i"))
		i++;
	while (arg[i] && ft_strchr(arg[i], '='))
		i++;
	newarg = cpytab(newarg, arg + i);
	return (newarg);
}

static void	clean_init(t_init *init)
{
	t_hist	*tmp;

	while (init->historic)
	{
		tmp = init->historic;
		ft_strdel(&init->historic->line);
		init->historic->prev = NULL;
		init->historic = init->historic->next;
		tmp->next = NULL;
		ft_memdel((void**)&tmp);
	}
		free_list(&init->new_env);
		free_list(&init->loc_env);
}

int			ft_env_i(t_env *new, t_init *init, t_ast *ast, char **arg)
{
	t_init	initmp;
	t_ast	*astmp;

	(void)init;
	new = fill_env(new, arg);
	if (new || (!new && arg[1] && arg[2]))
	{
		init_all(NULL, &initmp);
		astmp = init_ast();
		free_list(&initmp.new_env);
		initmp.new_env = new;
		ft_setenv(&initmp.loc_env, "PATH", "/bin:/usr/bin");
		astmp->cmd = init_cmd();
		astmp->value = CMD;
		astmp->cmd->arg = shift_arg(ast->cmd->arg);
		exec_start(astmp, &initmp);
		clean_ast(&astmp);
		clean_init(&initmp);
	}
	return (0);
}

int			usage_env(char *str)
{
	if (str[1])
	{
		ft_printf_fd(STDERR_FILENO, "env: illegal option -- %s\n", str + 1);
		ft_printf_fd(STDERR_FILENO,
				"usage: env [-i] [name=value ...] [utility[argument ...]]\n");
	}
	return (1);
}

int			ft_env(t_init *init, t_ast *ast, char **arg)
{
	t_env	*new;

	new = NULL;
	if (!arg[1])
		return (ft_print_env(init->new_env));
	else if (ft_strequ(arg[1], "-i") || ft_strequ(arg[1], "-"))
		new = NULL;
	else if (arg[1][0] == '-')
		return (usage_env(arg[1]));
	else
		new = cpyenv(init->new_env);
	return (ft_env_i(new, init, ast, arg));
}
