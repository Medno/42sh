/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:42:52 by hlely             #+#    #+#             */
/*   Updated: 2018/03/21 15:49:46 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		only_redir(t_ast *ast)
{
	t_redir	*redir;

	if (!redirection(ast->cmd))
		return (1);
	redir = ast->cmd->redir;
	while (redir)
	{
		close(redir->fd_out);
		redir = redir->next;
	}
	return (0);
}
