/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipefd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 11:25:33 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 11:49:15 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	del_one_pipe(t_pipe **pid)
{
	if (*pid)
	{
		(*pid)->fd = 0;
		(*pid)->next = NULL;
		free(*pid);
		*pid = NULL;
	}
}

void		del_pipe(t_pipe **pid)
{
	t_pipe	*tmp;

	while (*pid)
	{
		tmp = (*pid)->next;
		del_one_pipe(pid);
		*pid = tmp;
	}
}

t_pipe		*newpipe(int fd)
{
	t_pipe	*new;

	if (!(new = (t_pipe*)malloc(sizeof(t_pipe))))
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void		pipe_addlast(t_pipe **pipe, int fd)
{
	t_pipe	*start;

	start = *pipe;
	if (!*pipe)
	{
		*pipe = newpipe(fd);
		return ;
	}
	while (*pipe && (*pipe)->next)
		*pipe = (*pipe)->next;
	(*pipe)->next = newpipe(fd);
	*pipe = start;
}

int			get_newfd(t_pipe **pipe)
{
	int		fd;
	t_pipe	*tmp;

	fd = 12;
	tmp = *pipe;
	while (tmp)
	{
		fd = tmp->fd;
		tmp = tmp->next;
	}
	pipe_addlast(pipe, fd + 1);
	return (fd + 1);
}
