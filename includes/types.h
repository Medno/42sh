/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:08:58 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/16 11:41:20 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "sh.h"

typedef struct		s_line
{
	char			c;
	int				index;
	struct s_line	*next;
	struct s_line	*prev;
}					t_line;

typedef struct		s_curs
{
	int				x;
	int				y;
	int				xmax;
	int				ymax;
	int				nl;
	struct winsize	screen;
}					t_curs;

typedef struct		s_hist
{
	char			*line;
	int				nb;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_lcomp
{
	char			*cmd;
	struct s_lcomp	*next;
	struct s_lcomp	*prev;
}					t_lcomp;

typedef struct		s_comp
{
	char			*cmd;
	int				pos;
	t_lcomp			*list;
	t_lcomp			*current;
	char			*str;
	char			*dir;
	int				reset;
}					t_comp;

typedef struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef enum		e_token
{
	NONE, WORD, OP, QUOTE, IO_NUMBER, EOI, AND_IF, OR_IF, DSEMI, NEWLINE,
	DLESS, DGREAT, LESSAND, GREATAND, LESSGREAT, DLESSDASH, CLOBBER,
	ANDGREAT, ANDLESS, IO_HERE, CMD, PIPE, SEMI, L_PAREN, R_PAREN,
	L_BRACK, R_BRACK, L_BRACE, R_BRACE, BANG
}					t_token;

typedef struct		s_lex
{
	t_token			token;
	char			*value;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

typedef struct		s_redir
{
	int				fd_in;
	int				fd_out;
	char			*token;
	char			**file;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_cmd
{
	char			**arg;
	t_redir			*redir;
}					t_cmd;

typedef struct		s_ast
{
	t_token			value;
	t_cmd			*cmd;
	int				pipefd[2];
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_path
{
	char			*s;
	int				perms;
	char			type;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct		s_edit
{
	t_line			**current;
	t_hist			**histo;
	t_curs			curseur;
	t_comp			*comp;
	t_env			*env;
	t_env			*loc;
	int				prompt_len;
}					t_edit;

typedef struct		s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}					t_pid;

typedef struct		s_pipe
{
	int				fd;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_init
{
	char			*str;
	char			*pwd;
	int				stop;
	int				dollar;
	t_pipe			*pipe;
	t_pid			*pid_list;
	t_lex			*lex;
	t_env			*loc_env;
	t_env			*new_env;
	t_env			*env_tmp;
	t_hist			*historic;
	t_ast			*ast;
	struct termios	current;
}					t_init;

typedef struct		s_type
{
	int				value;
	int				(*f)(t_cmd *cmd, t_lex *lex);
}					t_type;
#endif
