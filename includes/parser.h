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
t_cmd				*ast_to_struct(t_ast *ast);
void				print_cmd(t_cmd *cmd);
void				ft_clean_redir(t_redir *redir);
void				ft_clean_cmd(t_cmd *cmd);

#endif
