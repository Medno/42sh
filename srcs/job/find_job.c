/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 08:50:54 by hlely             #+#    #+#             */
/*   Updated: 2018/03/20 09:11:04 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_job	*find_job(pid_t pgid, t_job *job)
{
	t_job	*tmp;

	tmp = job;
	while (tmp)
	{
		if (tmp->pgid == pgid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
