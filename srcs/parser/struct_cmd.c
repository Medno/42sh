/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 13:17:33 by hlely             #+#    #+#             */
/*   Updated: 2018/03/07 13:18:05 by hlely            ###   ########.fr       */
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
			ft_memdel((void **)tmp);
			tmp = tmp->next;
		}
		tmp = next_phrase;
	}
}
