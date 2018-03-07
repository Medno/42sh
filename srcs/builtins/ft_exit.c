/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:57:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/07 14:57:38 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	final_exit(t_init *init, unsigned char x)
{
	ft_cfmakedefault(&init->current);
	hist_to_file(init->historic);
	ft_strdel(&init->str);
	free_list(&init->new_env);
	exit(x);
}

void		ft_exit(t_init *init)
{
	unsigned char	ret;
	int				i;
	int				check;

	ret = 0;
	check = 0;
	i = -1;
	if (init->cmd->arg[1])
	{
		while (init->cmd->arg[1][++i])
		{
			if (!ft_isdigit(init->cmd->arg[1][i]))
			{
				check = -1;
				ret = 255;
				break ;
			}
			ret = (unsigned char)ft_atoi(init->cmd->arg[1]);
		}
	}
	ft_printf("{tred}{bold}exit{eoc}\n");
	if (check == -1)
		ft_printf_fd(STDERR_FILENO,
			"42sh: exit: %s: numeric argument required\n", init->cmd->arg[1]);
	final_exit(init, ret);
}
