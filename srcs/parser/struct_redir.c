/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/07 13:15:09 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_clean_redir(t_redir *redir)
{
	t_redir *tmp;
	t_redir	*del;

	tmp = redir;
	while (tmp)
	{
		del = tmp;
		tmp = tmp->next;
		ft_strdel(&(del->file));
		ft_strdel(&(del->token));
		del->next = NULL;
		ft_memdel((void **)&del);
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
