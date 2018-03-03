#ifndef PARSER_H
# define PARSER_H

# include "sh.h"

/*
** parser >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
void				paste_last_hist(t_hist **histo);
int					parser(t_init *init);
t_ast				*build_ast(t_lex *first);
t_ast				*init_ast(void);
t_ast				*io_file(t_lex *first);
t_ast				*io_redirect(t_lex *first);
void				del_ast(t_ast **root);
void				print_ast(t_ast *root, char *pos);
int					is_redir(t_lex *tmp);

#endif
