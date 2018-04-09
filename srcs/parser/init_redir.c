/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:36:27 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/09 11:54:48 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	clean_one_redir(t_redir **del)
{
	if (*del)
	{
		ft_freetab((*del)->file);
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
