#ifndef PARSER_H
# define PARSER_H

# include "sh.h"

/*
** parser >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					parser(t_init *init);
int					repeat_line(t_init *line, t_lex *tmp);
char				*line_edit(int len_prompt, t_init *init);
int					check_first(t_lex *first);
int					err_pars(t_lex *tmp);
int					err_eof(void);
/*
** ast
*/
t_ast				*init_ast(void);
void				clean_ast(t_ast **root);
t_ast				*build_ast(t_init *init, t_lex *first);
void				paste_last_hist(t_hist **histo);
void				print_ast(t_ast *root, char *pos);
/*
** command
*/
t_cmd				*init_cmd(void);
t_redir				*init_redir(void);
void				clean_cmd(t_cmd **cmd);
void				clean_redir(t_redir **redir);
t_redir				*put_fd_in(t_redir *redir, t_lex *tmp);
t_cmd				*put_redir(t_cmd *cmd, t_lex *tmp, int *loop);
t_cmd				*put_in_cmd(t_init *init, t_cmd *cmd, t_lex *tmp);
int					is_redir(t_lex *tmp);
void				print_cmd(t_cmd *cmd);
/*
** expansions
*/
char				*exp_tilde(t_init *init, char *str, int len);
/*
** quote removal
*/
void				word_exp(t_init *init, t_ast *ast);
char				*delete_esc(t_init *init, char *str, int len);
char				*esc_backslash(char *str, int *i);
char				*esc_simple_qu(char *str, int *i, int len);
char				*esc_double_qu(t_init *init, char *str, int *i, int len);

#endif
