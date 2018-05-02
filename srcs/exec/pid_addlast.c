/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_addlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 20:15:54 by hlely             #+#    #+#             */
/*   Updated: 2018/05/02 11:51:13 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	del_one_pid(t_pid **pid)
{
	if (*pid)
	{
		(*pid)->pid = 0;
		(*pid)->next = NULL;
		free(*pid);
		*pid = NULL;
	}
}

void		del_pid(t_pid **pid)
{
	t_pid	*tmp;

	while (*pid)
	{
		tmp = (*pid)->next;
		del_one_pid(pid);
		*pid = tmp;
	}
}

t_pid		*newpid(pid_t proc)
{
	t_pid	*new;

	if (!(new = (t_pid*)malloc(sizeof(t_pid))))
		return (NULL);
	new->pid = proc;
	new->next = NULL;
	return (new);
}

void		pid_addlast(t_pid **pid, pid_t proc)
{
	t_pid	*start;

	start = *pid;
	if (!*pid)
	{
		*pid = newpid(proc);
		return ;
	}
	while (*pid && (*pid)->next)
		*pid = (*pid)->next;
	(*pid)->next = newpid(proc);
	*pid = start;
}
