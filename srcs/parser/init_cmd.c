/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 13:25:59 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/16 10:51:35 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->arg = NULL;
	cmd->redir = NULL;
	return (cmd);
}

void	clean_one_cmd(t_cmd **tmp)
{
	if (*tmp)
	{
		ft_freetab((*tmp)->arg);
		clean_redir(&(*tmp)->redir);
		ft_memdel((void **)tmp);
	}
}
