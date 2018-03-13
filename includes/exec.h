/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:53:32 by hlely             #+#    #+#             */
/*   Updated: 2018/03/13 13:33:02 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#ifndef EXEC_H
# define EXEC_H

void		del_one_pid(t_pid **pid);
void		del_pid(t_pid **pid);
void		launch_pipe(t_init *init, t_ast *ast);
void		launch_pipe_wofork(t_init *init, t_ast *ast);
void		wait_pipe(t_pid **pid);
void		print_pid(t_pid *pid);

int			launch_exec(t_init *init, t_ast *ast);
int			exec_start(t_init *init);
int			check_cmd(t_ast *ast, t_init *init);
int			check_builtins(char ***entry, t_init *init);
int			check_path(char *str, t_env **env, char **s_fin);
int			step_1(t_init init);

void		pid_addlast(t_pid **pid, pid_t proc);

#endif
