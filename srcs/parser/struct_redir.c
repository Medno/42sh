/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/07 14:42:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_one_redir(t_redir **del)
{
	if (*del)
	{
		ft_strdel(&(*del)->file);
		ft_strdel(&(*del)->token);
		(*del)->next = NULL;
		ft_memdel((void **)del);
	}
}

void	clean_redir(t_redir **redir)
{
	if (*redir && (*redir)->next)
		clean_redir(&(*redir)->next);
	clean_one_redir(redir);
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
