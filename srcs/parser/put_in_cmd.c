/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:23:29 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/09 11:40:31 by pchadeni         ###   ########.fr       */
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

void	redir_pushback(t_cmd *cmd, t_redir *redir)
{
	t_redir	*redir_tmp;

	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		redir_tmp = cmd->redir;
		while (redir_tmp && redir_tmp->next)
			redir_tmp = redir_tmp->next;
		redir_tmp->next = redir;
	}
}

void	put_redir(t_cmd *cmd, t_lex *tmp, int *loop)
{
	t_redir	*redir;

	*loop = 2;
	redir = init_redir();
	redir = put_fd_in(redir, tmp);
	if (tmp->token == IO_NUMBER)
	{
		tmp = tmp->next;
		(*loop)++;
	}
	redir->token = ft_strdup(tmp->value);
	if (is_number(tmp->next->value))
		redir->fd_out = ft_atoi(tmp->next->value);
	else
		redir->file = ft_addstr_tab(redir->file, tmp->next->value);
	redir_pushback(cmd, redir);
}

t_cmd	*put_in_cmd(t_cmd *cmd, t_lex *tmp)
{
	char	*check_expans;

	if (tmp->token != EOI)
	{
		check_expans = ft_strdup(tmp->value);
		if (check_expans)
			cmd->arg = ft_addstr_tab(cmd->arg, check_expans);
		ft_strdel(&check_expans);
	}
	return (cmd);
}
