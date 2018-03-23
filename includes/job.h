/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 08:51:33 by hlely             #+#    #+#             */
/*   Updated: 2018/03/23 10:47:28 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H

# include "sh.h"

int				is_stopped(t_job *job);
int				is_completed(t_job *job);

t_job			*newjob(void);
t_job			*find_job(pid_t pgid, t_job *job);
void			job_pushback(t_job **job, t_job *new);

t_proc			*newproc(void);
void			proc_pushback(t_proc **job, t_proc *new);
#endif
