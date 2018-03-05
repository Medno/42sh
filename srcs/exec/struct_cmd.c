/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/05 13:47:23 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_clean_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	t_cmd *next_phrase;

	tmp = cmd;
	next_phrase = cmd;
	while (next_phrase)
	{
		next_phrase = tmp->next_semi;
		while (tmp)
		{
			ft_strdel(&(tmp->separ));
			ft_freetab(tmp->arg);
			ft_clean_redir(tmp->redir);
			free(tmp);
			tmp = tmp->next;
		}
		tmp = next_phrase;
	}
}

t_cmd	*cmd_push_back(t_cmd *cmd, t_cmd *new)
{
	t_cmd *tmp;

	if (!cmd)
		return (new);
	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (cmd);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*ret;

	ret = ft_memalloc(sizeof(t_cmd));
	return (ret);
}
