/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:53:32 by hlely             #+#    #+#             */
/*   Updated: 2018/03/12 15:58:10 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#ifndef EXEC_H
# define EXEC_H

void		launch_pipe(t_init *init, t_ast *ast);

int			launch_exec(t_init *init, t_ast *ast);
int			exec_start(t_init *init);
int			check_cmd(t_cmd *cmd, t_init *init);
int			check_builtins(char ***entry, t_init *init);
int			check_path(char *str, t_env **env, char **s_fin);
int			step_1(t_init init);

#endif
