/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_addlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 20:15:54 by hlely             #+#    #+#             */
/*   Updated: 2018/03/12 20:21:00 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_pid		*newpid(pid_t proc)
{
	t_pid	*new;

	if (!(new = (t_pid*)malloc(sizeof(t_pid))))
		return (NULL);
	new->pid = proc;
	return (new);
}

t_pid		*pid_addlast(t_pid *pid, pid_t proc)
{
	t_pid	*start;

	start = pid;
	if (!pid)
		return (newpid(proc));
	while (pid && pid->next)
		pid = pid->next;
	pid->next = newpid(proc);
	return (start);
}
