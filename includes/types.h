/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:08:58 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/05 12:22:14 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "sh.h"
# include "line_edit.h"

typedef struct		s_line
{
	char			c;
	int				index;
	int				select;
	struct s_line	*next;
	struct s_line	*prev;
}					t_line;

typedef struct		s_curs
{
	int				x;
	int				y;
	int				xmax;
	int				ymax;
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
}					t_lcomp;

typedef struct		s_comp 
{
	char			*cmd;
	int				pos;
	t_lcomp			*list;
	t_lcomp			*current;
	char			*str;
	char			*dir;
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
	DLESS, DGREAT, LESSAND, GREATAND, LESSGREAT, DLESSDASH, CLOBBER
}					t_token;

typedef struct		s_lex
{
	t_token			token;
	char			*value;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

typedef struct		s_ast
{
	char			*value;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_edit
{
	t_line			**current;
	t_hist			**histo;
	t_curs			curseur;
	t_comp			*comp;
	t_env			*env;
	int				prompt_len;
}					t_edit;

typedef struct		s_init
{
	char			*str;
	t_lex			*lex;
	t_env			*new_env;
	t_hist			*historic;
	struct termios	current;
}					t_init;

typedef struct		s_redir
{
	int				fd_in;
	int				fd_out;
	char			*token;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_cmd
{
	char			*v_cmd;
	char			**arg;
	t_redir			*redir;
	char			*separ;
	struct s_cmd	*next;
	struct s_cmd	*next_semi;
}					t_cmd;

typedef struct		s_type
{
	int				value;
	int				(*f)(t_cmd *cmd, t_lex *lex);
}					t_type;

#endif
