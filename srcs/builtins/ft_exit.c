/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:57:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/10 17:23:23 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	final_exit(t_init *init, unsigned char x, char **entry)
{
	if (entry)
		ft_freetab(entry);
	ft_cfmakeinit(&init->current);
	hist_to_file(init->historic);
	ft_strdel(&init->str);
	free_list(&init->new_env);
	if (x != 255)
		x = g_status;
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
				init->ast->cmd->arg[1]);
				return (final_exit(init, 255, arg));
			}
		}
		ret = (unsigned char)ft_atoi(arg[1]);
	}
	return (final_exit(init, ret, arg));
}
