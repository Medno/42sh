/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 08:55:59 by hlely             #+#    #+#             */
/*   Updated: 2018/03/20 08:59:12 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_stopped(t_job *job)
{
	t_proc	*proc;

	proc = job->proc;
	while (proc)
	{
		if (!proc->completed || !proc->stopped)
			return (0);
		proc = proc->next;
	}
	return (1);
}

int		is_completed(t_job *job)
{
	t_proc	*proc;

	proc = job->proc;
	while (proc)
	{
		if (!proc->completed)
			return (0);
		proc = proc->next;
	}
	return (1);
}
