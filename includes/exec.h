/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:53:32 by hlely             #+#    #+#             */
/*   Updated: 2018/03/14 10:50:42 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#ifndef EXEC_H
# define EXEC_H

void		del_one_pid(t_pid **pid);
void		del_pid(t_pid **pid);
void		setup_pipe(t_ast *ast);
void		close_pipe(t_ast *ast);
void		launch_pipe(t_init *init, t_ast *ast, int std_fd[]);
void		launch_and(t_init *init, t_ast *ast, int std_fd[]);
void		launch_or(t_init *init, t_ast *ast, int std_fd[]);
void		launch_semi(t_init *init, t_ast *ast, int std_fd[]);
void		wait_pipe(t_pid **pid);

int			launch_exec(t_init *init, t_ast *ast, int std_fd[]);
int			exec_start(t_init *init);
int			check_cmd(t_ast *ast, t_init *init);
int			fork_cmd(t_init *init, t_ast *ast, char *path);
int			is_builtin(char *str);
int			check_builtins(char ***entry, t_cmd *cmd, t_init *init);
int			check_path(char *str, t_env **env, char **s_fin);
int			step_1(t_init init);

void		pid_addlast(t_pid **pid, pid_t proc);

#endif
