/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:17:42 by hlely             #+#    #+#             */
/*   Updated: 2018/03/08 20:04:23 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "sh.h"

#define BADFD		-2
#define NOSUCHFILE	-3
#define NOPERM		-4
#define OPENFAIL	-5
#define AMBIGOUS	-6
#define TOCLOSE		-10

int		redirection(t_cmd *cmd);

char	*create_newheredoc(char *heredoc);

t_redir	*handle_simple(t_redir *redir);
t_redir	*handle_simplefd(t_redir *redir);
t_redir	*handle_double(t_redir *redir);
t_redir	*handle_back(t_redir *redir);
t_redir	*handle_backfd(t_redir *redir);
t_redir	*handle_heredoc(t_redir *redir);
t_redir	*handle_redirall(t_redir *redir);
t_redir	*handle_rw(t_redir *redir);

void	del_heredoc(void);

/*
** Error case >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

int		file_error(char *file);
void	which_error(int error, char *err_file);

/*
** Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

void	saving_fd(int fd[]);
int		reset_fd(int fd[], t_redir *redir);
#endif
