/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:23:29 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/14 14:36:09 by pchadeni         ###   ########.fr       */
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
	t_cmd	*cmd_tmp;

	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		cmd_tmp = cmd;
		while (cmd->redir && cmd->redir->next)
			cmd->redir = cmd->redir->next;
		cmd->redir->next = redir;
		cmd = cmd_tmp;
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
		redir->file = ft_strdup(tmp->next->value);
	redir_pushback(cmd, redir);
}

t_cmd	*put_in_cmd(t_init *init, t_cmd *cmd, t_lex *tmp)
{
	char	*check_expans;

	if (tmp->token != EOI)
	{
		check_expans = ft_strdup(tmp->value);
		if (check_expans[0] == '~')
			check_expans = exp_tilde(init, check_expans,
					ft_strlen(check_expans));
		check_expans = delete_esc(init, check_expans, ft_strlen(check_expans));
		if (check_expans)
			cmd->arg = ft_addstr_tab(cmd->arg, check_expans);
		ft_strdel(&check_expans);
	}
	return (cmd);
}
