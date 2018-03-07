/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:50:47 by hlely             #+#    #+#             */
/*   Updated: 2018/03/07 10:26:56 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*handle_redir(t_redir *redir)
{
	if (ft_strequ(redir->token, ">"))
		redir = handle_simple(redir);
	else if (ft_strequ(redir->token, ">&"))
		redir = handle_simplefd(redir);
	else if (ft_strequ(redir->token, "<&"))
		redir = handle_backfd(redir);
	else if (ft_strequ(redir->token, ">>"))
		redir = handle_double(redir);
	else if (ft_strequ(redir->token, "<"))
		redir = handle_back(redir);
	else if (ft_strequ(redir->token, "<<"))
		redir = handle_heredoc(redir);
	else if (ft_strequ(redir->token, "&>"))
		redir = handle_redirall(redir);
	return (redir);
}

int		redirection(t_cmd *cmd)
{
	t_redir	*tmp;

	while (cmd && cmd->redir)
	{
		tmp = cmd->redir;
		cmd->redir = handle_redir(cmd->redir);
		if (!cmd->redir)
		{
			cmd->redir = tmp;
			return (0);
		}
		cmd->redir = cmd->redir->next;
	}
	ft_putendl_fd("Ceci est la sortie standard", STDOUT_FILENO);
	ft_putendl_fd("Ceci est la sortie d'erreur", STDERR_FILENO);
	cmd->redir = tmp;
	return (1);
}
