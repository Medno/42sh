/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:53:32 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 11:39:07 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "sh.h"

void		del_pid(t_pid **pid);
void		setup_pipe(t_ast *ast);
void		close_pipe(t_ast *ast);
int			clean_pipe(t_init *init);
void		launch_pipe(t_init *init, t_ast *ast, int std_fd[], int error);
void		launch_and(t_init *init, t_ast *ast, int std_fd[], int error);
void		launch_or(t_init *init, t_ast *ast, int std_fd[], int error);
int			wait_pipe(t_pid **pid, int sig);

int			delete_space(t_ast *ast);
int			only_redir(t_init *init, t_ast *ast);

int			launch_exec(t_init *init, t_ast *ast, int std_fd[], int error);
int			exec_start(t_ast *ast, t_init *init);
int			check_cmd(t_ast *ast, t_init *init);
int			fork_cmd(t_init *init, t_ast *ast, char *path);
int			is_builtin(char *str);
int			check_builtins(char ***entry, t_cmd *cmd, t_ast *ast, t_init *init);
int			check_path(char **arg, t_init *init, char **s_fin, int print);
int			check_bin(char *str, t_init *init, char **s_fin, int print);

void		pid_addlast(t_pid **pid, pid_t proc);

int			check_slash(t_init *init, char *str, char **s_fin, int print);

int			check_error(int ret, char *str, int print);
int			path_error(char *str);
void		exit_error(int ret, char *str);
void		error_execve(void);
void		signal_error(int signal, int pid);

int			get_newfd(t_pipe **pipe);
void		pipe_addlast(t_pipe **pipe, int fd);
void		del_pipe(t_pipe **pipe);
#endif
