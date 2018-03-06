/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/06 17:53:47 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
