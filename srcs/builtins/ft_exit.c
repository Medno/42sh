/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:57:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/16 12:21:57 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	final_exit(t_init *init, unsigned char x)
{
	ft_cfmakeinit(&init->current);
	hist_to_file(init->historic);
	ft_strdel(&init->str);
	free_list(&init->new_env);
	free_list(&init->loc_env);
	free_list(&init->env_tmp);
	ft_strdel(&init->pwd);
	del_pid(&init->pid_list);
	clean_ast(&init->ast);
	del_lex(&init->lex);
	if (x == 0)
		x = g_oldstatus;
	exit(x);
	return (0);
}

int			ft_exit(t_init *init, char **arg)
{
	unsigned char	ret;
	int				i;

	ret = 0;
	i = -1;
	ft_printf_fd(STDIN_FILENO, "{tred}{bold}exit{eoc}\n");
	if (arg && arg[0] && arg[1] && arg[2] != NULL)
	{
		ft_putendl_fd("42sh: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	else if (arg && arg[0] && arg[1])
	{
		while (arg[1][++i])
		{
			if (!ft_isdigit(arg[1][i]))
			{
				ft_printf_fd(2, "42sh: exit: %s: numeric argument required\n",
				arg[1]);
				return (final_exit(init, 255));
			}
		}
		ret = (unsigned char)ft_atoi(arg[1]);
	}
	return (final_exit(init, ret));
}
