/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 09:12:30 by hlely             #+#    #+#             */
/*   Updated: 2018/03/20 09:12:35 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_job		*newjob(void)
{
	t_job	*new;

	new = (t_job*)ft_memalloc(sizeof(t_job));
	return (new);
}

void		job_pushback(t_job **job, t_job *new)
{
	t_job	*start;

	start = *job;
	if (!start)
		*job = new;
	else
	{
		while (start->next)
			start = start->next;
		start->next = new;
	}
}
