/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:48:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 11:12:55 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "sh.h"
# include "types.h"

# define ERROR_TYPE		0
# define CMD			1
# define ARG			2
# define REDIR			3
# define REDIR_FILE		4
# define SEPAR			5
# define SEMI_COLON		6

int		init_exec(t_lex *lex);
t_lex 	*fill_cmd(t_cmd *cmd, t_lex *lex);
int		do_exec(t_cmd *cmd);

/*
**	FILL CMD
*/
int		add_redir_token(t_cmd *cmd, t_lex *lex);
int		add_redir_file(t_cmd *cmd, t_lex *lex);
int		add_arg(t_cmd *cmd, t_lex *lex);
int		stop_fill(t_cmd *cmd, t_lex *lex);

/*
**	STRUCT CMD
*/

void	ft_clean_cmd(t_cmd *cmd);
t_cmd	*cmd_push_back(t_cmd *cmd, t_cmd *new);
t_cmd	*init_cmd(void);

/*
**	STRUCT REDIR
*/

void	ft_clean_redir(t_redir *redir);
t_redir	*redir_push_back(t_redir *redir, t_redir *new);
t_redir	*init_redir(void);

#endif
