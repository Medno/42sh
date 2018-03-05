/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:50:47 by hlely             #+#    #+#             */
/*   Updated: 2018/03/05 17:59:33 by hlely            ###   ########.fr       */
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

t_cmd	*redirection(t_cmd *cmd)
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
				tmp2->redir = handle_redir(tmp2->redir);
				tmp2->redir = tmp2->redir->next;
			}
			tmp2->redir = tmp_redir;
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next_semi;
	}
	print_cmd2(cmd);
	return (cmd);
}
