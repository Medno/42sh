/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 13:25:59 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/07 14:43:13 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*init_cmd_p(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->arg = NULL;
	cmd->redir = NULL;
	cmd->separ = NULL;
	cmd->next = NULL;
	cmd->next_semi = NULL;
	return (cmd);
}

void	clean_one_cmd(t_cmd **tmp)
{
	if (*tmp)
	{
		ft_strdel(&(*tmp)->separ);
		ft_freetab((*tmp)->arg);
		clean_redir(&(*tmp)->redir);
		(*tmp)->next = NULL;
		(*tmp)->next_semi = NULL;
		ft_memdel((void **)tmp);
	}
}

void	clean_next(t_cmd **cmd)
{
	if (*cmd && (*cmd)->next)
		clean_next(&(*cmd)->next);
	clean_one_cmd(cmd);
}


void	clean_cmd(t_cmd **cmd)
{
	if (*cmd && (*cmd)->next_semi)
		clean_cmd(&(*cmd)->next_semi);
	clean_next(cmd);
}
