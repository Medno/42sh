/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:17:42 by hlely             #+#    #+#             */
/*   Updated: 2018/05/16 15:40:28 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "sh.h"

# define RESETALL	0
# define RESETFILE	1
# define BADFD		-2
# define NOSUCHFILE	-3
# define NOPERM		-4
# define OPENFAIL	-5
# define AMBIGOUS	-6
# define TOCLOSE	-10

int		redirection(t_init *init, t_cmd *cmd);

char	*create_newheredoc(char *heredoc);

t_redir	*handle_simple(t_redir *redir);
t_redir	*handle_simplefd(t_init *init, t_redir *redir);
t_redir	*handle_double(t_redir *redir);
t_redir	*handle_back(t_redir *redir);
t_redir	*handle_backfd(t_redir *redir);
t_redir	*handle_redirall(t_redir *redir);
t_redir	*handle_rw(t_redir *redir);
t_redir	*handle_closingfd(t_redir *redir);
t_redir	*handle_allfd(t_redir *redir);

void	del_heredoc(void);

/*
** Error case >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

int		is_in_pipelist(t_pipe *pipe, int fd);
int		file_error(char *file);
t_redir	*backup_error(void);
t_redir	*which_error(int error, char *err_file);

/*
** Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

void	saving_fd(int fd[]);
void	close_fd(t_init *init, t_cmd *cmd);
int		reset_fd(t_init *init, int fd[], t_cmd *cmd);
#endif
