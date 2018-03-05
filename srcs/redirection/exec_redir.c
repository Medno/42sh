/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:14:47 by hlely             #+#    #+#             */
/*   Updated: 2018/03/05 20:25:15 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		exec_redir(t_redir *redir)
{
	if (redir->fd_out < -1)
		return (which_error(redir->fd_out));
	if (redir->file && ft_strequ(redir->file, "-"))
		return (close_fd(redir));
	return (0);
}

int		loop_redir(t_cmd *cmd)
{
	t_cmd	*tmp1;
	t_cmd	*tmp2;
	t_redir	*tmp_redir;

	tmp1 = cmd;
	while (tmp1)
	{
		tmp2 = tmp1;
		while (tmp2)
		{
			tmp_redir = tmp2->redir;
			while (tmp2->redir)
			{
				if (exec_redir(tmp2->redir))
					return (1);
				tmp2->redir = tmp2->redir->next;
			}
			tmp2->redir = tmp_redir;
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next_semi;
	}
	print_cmd2(cmd);
	return (0);
}
