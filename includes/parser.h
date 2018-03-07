#ifndef PARSER_H
# define PARSER_H

# include "sh.h"

/*
** parser >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					parser(t_init *init);
/*
** ast
*/
t_ast				*build_ast(t_lex *first);
t_ast				*init_ast(void);
t_ast				*io_file(t_lex *first);
t_ast				*io_redirect(t_lex *first);
void				del_ast(t_ast **root);
void				print_ast(t_ast *root, char *pos);
void				paste_last_hist(t_hist **histo);
/*
** command
*/
t_cmd				*init_cmd_p(void);
void				clean_cmd(t_cmd **cmd);
t_redir				*init_redir(void);
void				clean_redir(t_redir **redir);
int					is_redir(t_lex *tmp);
t_cmd				*ast_to_struct(t_ast *ast);
void				print_cmd(t_cmd *cmd);
/*
** quote remove
*/
void				quote_remove(t_init *init);
char				*esc_backslash(char *res, char *str, int *i);
char				*esc_simple_qu(char *res, char *str, int *i, int len);
char				*esc_double_qu(char *res, char *str, int *i, int len);

#endif
