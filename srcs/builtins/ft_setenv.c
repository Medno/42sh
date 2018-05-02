/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:15:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/02 15:33:18 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_env	*new_env(char *name, char *content)
{
	t_env	*new_elem;

	if (!(new_elem = malloc(sizeof(t_env))))
	{
		ft_putendl_fd("pksh: setenv: Cannot allocate memory", 2);
		return (NULL);
	}
	new_elem->name = ft_strdup(name);
	new_elem->content = ft_strdup(content);
	new_elem->next = NULL;
	return (new_elem);
}

int				ft_setenv(t_env **env, char *name, char *content)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && tmp->next && ft_strcmp(name, tmp->name))
		tmp = tmp->next;
	if (!content)
	{
		ft_putendl_fd("setenv: invalid argument", STDERR_FILENO);
		return (1);
	}
	if (tmp && !ft_strcmp(name, tmp->name))
	{
		free(tmp->content);
		tmp->content = ft_strdup(content);
	}
	else
	{
		if (!*env)
			*env = new_env(name, content);
		else
			tmp->next = new_env(name, content);
	}
	return (0);
}

int				ft_setenv_init(t_init *init, char **arg)
{
	if (!arg[1])
	{
		ft_print_env(init->new_env, 0);
		return (0);
	}
	if (ft_tablen(arg) > 3)
	{
		ft_printf_fd(STDERR_FILENO, "setenv: Too many arguments.\n");
		return (1);
	}
	if (!arg[1] || !arg[2] || ft_strchr(arg[1], '='))
	{
		ft_printf_fd(STDERR_FILENO, "setenv: usage: setenv [name] [value]\n");
		return (1);
	}
	ft_getenv(&init->loc_env, arg[1]) ? ft_unsetenv(&init->loc_env, arg[1]) : 0;
	if (arg && arg[1] && !is_valid_identifier("setenv", arg[1], PRINT))
		return (1);
	return (ft_setenv(&init->new_env, arg[1], arg[2]));
}
