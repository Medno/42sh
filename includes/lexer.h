#ifndef LEXER_H
# define LEXER_H

# include "sh.h"

/*
** lexer manipulation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
t_lex				*lexer(char *str);
t_lex				*init_lexer(void);
void				del_one_lex(t_lex *tmp);
void				del_lex(t_lex *first);
void				print_lex(t_lex *first);
t_lex				*get_lex(t_lex *first, t_token token, char *value);
int					isredir(char c);
int					is_op(char c, char buf[]);
int					is_esc(char c);
int					is_number(char buf[]);

#endif
