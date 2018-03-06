/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:50:47 by hlely             #+#    #+#             */
/*   Updated: 2018/03/06 10:17:57 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_cmd2(t_cmd *cmd)
{
	int	i;
	t_cmd	*tmp;
	t_cmd	*tmp_2;
	t_redir	*leak;

	tmp = cmd;
	while (tmp)
	{
		ft_printf("Nouvelle commande :\n");
		tmp_2 = tmp;
		while(tmp_2)
		{
			i = 0;
			if (tmp_2->arg)
			{
				while (tmp_2->arg[i])
				{
					ft_printf("Parametre %d : |%s|\n", i, tmp_2->arg[i]);
					i++;
				}
			}
			if (tmp_2->separ)
				ft_printf("Separateur : |%s|\n", tmp_2->separ);
			leak = tmp_2->redir;
			while (leak)
			{
				ft_printf("fd_in : |%d|\ntoken : |%s|\nfd_out : ", leak->fd_in, leak->token);
				if (leak->file)
					ft_putstr(leak->file);
				ft_putchar(' ');
					ft_putnbr(leak->fd_out);
				ft_putchar('\n');
				leak = leak->next;
			}
			tmp_2 = tmp_2->next;
		}
		tmp = tmp->next_semi;
	}
}

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
	return (redir);
}

int		redirection(t_cmd *cmd)
{
	while (cmd && cmd->redir)
	{
		cmd->redir = handle_redir(cmd->redir);
		if (!cmd->redir)
			return (0);
		cmd->redir = cmd->redir->next;
	}
	return (1);
}
