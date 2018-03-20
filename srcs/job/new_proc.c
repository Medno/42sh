/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 09:12:16 by hlely             #+#    #+#             */
/*   Updated: 2018/03/20 09:12:18 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_proc		*newproc(void)
{
	t_proc	*proc;

	proc = (t_proc*)ft_memalloc(sizeof(t_proc));
	return (proc);
}

void		proc_pushback(t_proc **proc, t_proc *new)
{
	t_proc	*start;

	start = *proc;
	if (!start)
		*proc = new;
	else
	{
		while (start->next)
			start = start->next;
		start->next = new;
	}
}
