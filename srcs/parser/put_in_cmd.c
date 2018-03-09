/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:23:29 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/09 14:27:30 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*put_fd_in(t_redir *redir, t_lex *tmp)
{
	if (tmp->token == IO_NUMBER)
		redir->fd_in = ft_atoi(tmp->value);
	else if ((tmp->value[0] == '>' && !tmp->value[1]) || tmp->token == DGREAT)
		redir->fd_in = 1;
	else if ((tmp->value[0] == '<' && !tmp->value[1]) || tmp->token == DLESS ||
			tmp->token == DLESSDASH)
		redir->fd_in = 0;
	else
		redir->fd_in = -1;
	return (redir);
}

t_cmd	*put_redir(t_cmd *cmd, t_lex *tmp, int *loop)
{
	*loop = 2;
	cmd->redir = init_redir();
	cmd->redir = put_fd_in(cmd->redir, tmp);
	if (tmp->token == IO_NUMBER)
	{
		tmp = tmp->next;
		(*loop)++;
	}
	cmd->redir->token = ft_strdup(tmp->value);
	if (is_number(tmp->next->value))
		cmd->redir->fd_out = ft_atoi(tmp->next->value);
	else
		cmd->redir->file = ft_strdup(tmp->next->value);
	return (cmd);
}

t_cmd	*put_in_cmd(t_cmd *cmd, t_lex *tmp)
{
	if (tmp->token != EOI)
		cmd->arg = ft_addstr_tab(cmd->arg, tmp->value);
	return (cmd);
}
