/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:17:42 by hlely             #+#    #+#             */
/*   Updated: 2018/03/05 16:24:01 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "sh.h"

#define BADFD		-2
#define NOSUCHFILE	-3
#define NOPERM		-4
#define OPENFAIL	-5
#define TOCLOSE		-10

t_cmd	*redirection(t_cmd *cmd);

t_redir	*handle_simple(t_redir *redir);
t_redir	*handle_simplefd(t_redir *redir);
t_redir	*handle_double(t_redir *redir);
t_redir	*handle_back(t_redir *redir);
t_redir	*handle_heredoc(t_redir *redir);

/*
** Error case >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

int		bad_fd(int fd);
int		file_error(char *file);

#endif
