/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:08:58 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 18:27:01 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "sh.h"
# include "line_edit.h"

# define LEFT(x) ft_printf("\033[%dD", x)
# define RIGHT(x) ft_printf("\033[%dC", x)
# define DOWN(x) ft_printf("\033[%dB", x)
# define UP(x) ft_printf("\033[%dA", x)
# define NL ft_printf("\033E")

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
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

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

typedef struct		s_init
{
	char			*str;
	t_lex			*lex;
	t_env			*new_env;
	t_hist			*historic;
	struct termios	current;
}					t_init;

#endif
