/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 12:29:49 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/11 14:31:58 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "sh.h"

/*
** parser >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					parser(t_init *init);
int					repeat_heredoc(t_init *init, t_lex *tmp);
int					repeat_line(t_init *line, t_lex *tmp);
int					line_edit(char **line, int len_prompt, t_init *init);
int					is_redir(t_lex *tmp);
/*
** errors
*/
int					print_errpars(int index, char *str, char c);
int					check_first(t_lex *first);
int					err_pars(t_lex *tmp);
int					err_eof(void);
/*
** ast
*/
t_ast				*init_ast(void);
void				clean_ast(t_ast **root);
t_ast				*build_ast(t_lex *first);
void				paste_last_hist(t_hist **histo);
/*
** command
*/
t_cmd				*init_cmd(void);
t_redir				*init_redir(void);
void				clean_one_cmd(t_cmd **cmd);
void				clean_redir(t_redir **redir);
t_redir				*put_fd_in(t_redir *redir, t_lex *tmp);
void				put_redir(t_cmd *cmd, t_lex *tmp, int *loop);
t_cmd				*put_in_cmd(t_cmd *cmd, t_lex *tmp);

#endif
