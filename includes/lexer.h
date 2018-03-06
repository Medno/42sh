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
t_lex				*put_in_new(t_lex *new, char *buf);
int					isredir(char c);
int					is_op(char c, char buf[]);
int					is_esc(char c);
int					is_number(char buf[]);
/*
** All the steps for the lexer
*/
t_lex				*already_op(t_lex *new, char *str, int *i, char buf[]);
t_lex				*enter_quote(t_lex *new, char *str, int *i, char buf[]);
t_lex				*new_op(t_lex *new, char *str, int i, char buf[]);
t_lex				*close_new(t_lex *new, char buf[]);
void				concat_char(char *str, int i, char buf[]);
t_lex				*new_word(t_lex *new, char *str, int i, char *buf);
t_lex				*end_of_new(t_lex *new, char buf[]);

#endif
