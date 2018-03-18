/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:57:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/18 11:18:07 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	final_exit(t_init *init, unsigned char x, char ***entry)
{
	if (entry && *entry)
		ft_freetab(*entry);
	ft_cfmakeinit(&init->current);
	hist_to_file(init->historic);
	ft_strdel(&init->str);
	free_list(&init->new_env);
	exit(x);
	return (0);
}

int			ft_exit(t_init *init, char ***entry)
{
	unsigned char	ret;
	int				i;
	int				check;

	ret = 0;
	check = 0;
	i = -1;
	if (init->ast && init->ast->cmd && init->ast->cmd->arg[1])
	{
		while (init->ast->cmd->arg[1][++i])
		{
			if (!ft_isdigit(init->ast->cmd->arg[1][i]))
			{
				check = -1;
				ret = 255;
				break ;
			}
			ret = (unsigned char)ft_atoi(init->ast->cmd->arg[1]);
		}
	}
	ft_printf("{tred}{bold}exit{eoc}\n");
	if (check == -1)
		ft_printf_fd(STDERR_FILENO,
		"42sh: exit: %s: numeric argument required\n", init->ast->cmd->arg[1]);
	return (final_exit(init, ret, entry));
}
