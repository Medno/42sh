/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:50:47 by hlely             #+#    #+#             */
/*   Updated: 2018/03/05 16:35:52 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* void	print_cmd2(t_cmd *cmd) */
/* { */
/* 	int	i; */
/* 	t_cmd	*tmp; */
/* 	t_cmd	*tmp_2; */
/* 	t_redir	*leak; */

/* 	tmp = cmd; */
/* 	while (tmp) */
/* 	{ */
/* 		tmp_2 = tmp; */
/* 		while(tmp_2) */
/* 		{ */
/* 			i = 0; */
/* 			if (tmp_2->v_cmd) */
/* 			{ */
/* 				ft_putstr("Commande : "); */
/* 				ft_putendl(tmp_2->v_cmd); */
/* 			} */
/* 			if (tmp_2->arg) */
/* 			{ */
/* 				while (tmp_2->arg[i]) */
/* 				{ */
/* 					ft_putstr("Parametre : "); */
/* 					ft_putendl(tmp_2->arg[i]); */
/* 					i++; */
/* 				} */
/* 			} */
/* 			if (tmp_2->separ) */
/* 			{ */
/* 				ft_putstr("Separateur : "); */
/* 				ft_putendl(tmp_2->separ); */
/* 			} */
/* 			leak = tmp_2->redir; */
/* 			while (leak) */
/* 			{ */
/* 				ft_putstr("fd_in : "); */
/* 				ft_putnbr(tmp_2->redir->fd_in); */
/* 				ft_putstr("\ntoken : "); */
/* 				ft_putendl(tmp_2->redir->token); */
/* 				ft_putstr("fd_out : "); */
/* 				if (tmp_2->redir->file) */
/* 				{ */
/* 					ft_putstr("file:"); */
/* 					ft_putstr(tmp_2->redir->file); */
/* 				} */
/* 					ft_putstr("nbr:"); */
/* 					ft_putnbr(tmp_2->redir->fd_out); */
/* 				ft_putchar('\n'); */
/* 				leak = leak->next; */
/* 			} */
/* 			tmp_2 = tmp_2->next; */
/* 		} */
/* 		tmp = tmp->next_semi; */
/* 	} */
/* } */

t_redir	*handle_redir(t_redir *redir)
{
	if (ft_strequ(redir->token, ">"))
		redir = handle_simple(redir);
	if (ft_strequ(redir->token, ">&"))
		redir = handle_simplefd(redir);
	if (ft_strequ(redir->token, ">>"))
		redir = handle_double(redir);
	if (ft_strequ(redir->token, "<"))
		redir = handle_back(redir);
	if (ft_strequ(redir->token, "<<"))
		redir = handle_heredoc(redir);
	return (redir);
}

t_cmd	*redirection(t_cmd *cmd)
{
	t_cmd	*begin;
	t_redir	*tmp;

	begin = cmd;
	while (cmd)
	{
		tmp = cmd->redir;
		while (cmd->redir)
		{
			cmd->redir = handle_redir(cmd->redir);
			cmd->redir = cmd->redir->next;
		}
		cmd->redir = tmp;
		cmd = cmd->next;
	}
	return (begin);
}
