/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:57:14 by hlely             #+#    #+#             */
/*   Updated: 2018/04/16 12:22:59 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		unset_usage(void)
{
	ft_printf_fd(STDERR_FILENO, "42sh: usage: unset [-f] [-v] [name...]\n");
	return (1);
}

static int		set_bits(char c, int flag)
{
	if (c == 'f')
		flag |= 1;
	else if (c == 'v')
		flag |= 2;
	return (flag);
}

static int		not_real_unset(char **arg, int flags)
{
	int		i;
	int		ret;

	i = flags ? 2 : 1;
	ret = 0;
	while (arg[i])
	{
		if (!is_all_valid_identifier("unset", arg[i], PRINT))
		{
			i++;
			ret = 1;
			continue ;
		}
		i++;
	}
	return (ret);
}

static int		unset_for_real(t_env **loc, t_env **env, char **arg, int flags)
{
	int		i;
	int		ret;

	i = flags ? 2 : 1;
	ret = 0;
	while (arg[i])
	{
		if (!is_all_valid_identifier("unset", arg[i], PRINT))
		{
			i++;
			ret = 1;
			continue ;
		}
		if (is_in_env(*loc, arg[i]))
			ft_unsetenv(loc, arg[i]);
		else if (is_in_env(*env, arg[i]))
			ft_unsetenv(env, arg[i]);
		i++;
	}
	return (ret);
}

int				ft_unset(t_env **loc, t_env **env, char **arg)
{
	int		flags;
	char	c;

	flags = 0;
	c = 0;
	reset_ft_opt();
	while ((c = ft_getopt(ft_tablen(arg), arg, "fv")) != -1)
	{
		if (ft_strchr("fv", c))
			flags = set_bits(c, flags);
		else if (c == '?')
			return (unset_usage());
	}
	if ((flags & 1) && (flags & 2))
	{
		ft_printf_fd(STDERR_FILENO, "42sh: unset: cannot have flag f and v\n");
		return (1);
	}
	if (flags & 2 || flags == 0)
		return (unset_for_real(loc, env, arg, flags));
	return (not_real_unset(arg, flags));
}
