/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/06 17:34:19 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_clean_redir(t_redir *redir)
{
	t_redir *tmp;

	tmp = redir;
	while (tmp)
	{
		redir = redir->next;
		ft_strdel(&(tmp->file));
		ft_strdel(&(tmp->token));
		free(tmp);
		tmp = redir;
	}
}

t_redir	*init_redir(void)
{
	t_redir	*ret;

	ret = ft_memalloc(sizeof(t_redir));
	if (!ret)
		return (NULL);
	ret->fd_in = 1;
	ret->fd_out = -1;
	ret->token = NULL;
	ret->file = NULL;
	ret->next = NULL;
	return (ret);
}
