/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 14:41:23 by kyazdani         ###   ########.fr       */
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

t_redir	*redir_push_back(t_redir *redir, t_redir *new)
{
	t_redir *tmp;

	if (!redir)
		return (new);
	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (redir);
}

t_redir	*init_redir(void)
{
	t_redir	*ret;

	ret = ft_memalloc(sizeof(t_redir));
	return (ret);
}